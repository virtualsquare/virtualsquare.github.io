/*********************************P2TEST.C*******************************
 *
 *	Test program for the PandOS Kernel: phase 2.
 *
 *	Produces progress messages on Terminal0.
 *
 *	This is pretty convoluted code, so good luck!
 *
 *	Aborts as soon as an error is detected.
 *
 *	Modified by Michael Goldweber on June 19, 2020
 */

#include "../h/const.h"
#include "../h/types.h"

#include "/usr/include/umps3/umps/libumps.e"
/* or, if you have manually installed μMPS3 */
/* #include "/usr/local/include/umps3/umps/libumps.e" */

typedef unsigned int devregtr;

/* hardware constants */
#define PRINTCHR	2
#define BYTELEN	8
#define RECVD	5

#define CLOCKINTERVAL	100000UL	/* interval to V clock semaphore */

#define TERMSTATMASK	0xFF
#define CAUSEMASK		0xFF
#define VMOFF 			0xF8FFFFFF

#define SYSCAUSE		(0x8 << 2)
#define BUSERROR		6
#define RESVINSTR   	10
#define ADDRERROR		4
#define SYSCALLEXCPT	8

#define QPAGE			1024

#define IEPBITON		0x4
#define KUPBITON		0x8
#define KUPBITOFF		0xFFFFFFF7
#define TEBITON			0x08000000

#define CAUSEINTMASK	0xFD00
#define CAUSEINTOFFS	10

#define MINLOOPTIME		30000
#define LOOPNUM 		10000

#define CLOCKLOOP		10
#define MINCLOCKLOOP	3000

#define BADADDR			0xFFFFFFFF
#define	TERM0ADDR		0x10000254


/* system call codes */
#define	CREATETHREAD	  1	/* create thread */
#define	TERMINATETHREAD	2	/* terminate thread */
#define	PASSERN			    3	/* P a semaphore */
#define	VERHOGEN		    4	/* V a semaphore */
#define	WAITIO			    5	/* delay on a io semaphore */
#define	GETCPUTIME		  6	/* get cpu time used to date */
#define	WAITCLOCK		    7	/* delay on the clock semaphore */
#define	GETSPTPTR		    8	/* return support structure ptr. */

#define CREATENOGOOD	-1

/* just to be clear */
#define SEMAPHORE		int
#define NOLEAVES		4	/* number of leaves of p8 process tree */
#define MAXSEM			20


SEMAPHORE term_mut=1,	/* for mutual exclusion on terminal */
		s[MAXSEM+1],	/* semaphore array */
		testsem=0,		/* for a simple test */
		startp2=0,		/* used to start p2 */
		endp2=0,		  /* used to signal p2's demise */
		endp3=0,		  /* used to signal p3's demise */
		blkp4=1,		  /* used to block second incaration of p4 */
		synp4=0,		  /* used to allow p4 incarnations to synhronize */
		endp4=0,		  /* to signal demise of p4 */
		endp5=0,		  /* to signal demise of p5 */
		endp8=0,		  /* to signal demise of p8 */
		endcreate=0,	/* for a p8 leaf to signal its creation */
		blkp8=0;		  /* to block p8 */

state_t p2state, p3state, p4state, p5state,	p6state, p7state,p8rootstate,
        child1state, child2state, gchild1state, gchild2state, gchild3state, gchild4state;

/* support structure for p5 */
support_t pFiveSupport;

int		p1p2synch=0;	/* to check on p1/p2 synchronization */

int 	p8inc;			/* p8's incarnation number */
int		p4inc=1;		/* p4 incarnation number */

unsigned int p5Stack;	/* so we can allocate new stack for 2nd p5 */

int creation = 0; 				/* return code for SYSCALL invocation */
memaddr *p5MemLocation = 0;		/* To cause a p5 trap */

void	p2(),p3(),p4(),p5(),p5a(),p5b(),p6(),p7(),p7a(),p5prog(),p5mm();
void	p5sys(),p8root(),child1(),child2(),p8leaf();

extern void p5gen ();
extern void p5mm ();


/* a procedure to print on terminal 0 */
void print(char *msg) {

	char *s = msg;
	devregtr * base = (devregtr *) (TERM0ADDR);
	devregtr status;

	SYSCALL(PASSERN, (int)&term_mut, 0, 0);				/* P(term_mut) */
	while (*s != EOS) {
		*(base + 3) = PRINTCHR | (((devregtr) *s) << BYTELEN);
		status = SYSCALL(WAITIO, TERMINT, 0, 0);
		if ((status & TERMSTATMASK) != RECVD)
			PANIC();
		s++;
	}
	SYSCALL(VERHOGEN, (int)&term_mut, 0, 0);				/* V(term_mut) */
}


/* TLB-Refill Handler */
/* One can place debug calls here, but not calls to print */
void uTLB_RefillHandler () {

	setENTRYHI(0x80000000);
	setENTRYLO(0x00000000);
	TLBWR();

	LDST ((state_PTR) 0x0FFFF000);
}


/*********************************************************************/
/*                                                                   */
/*                 p1 -- the root process                            */
/*                                                                   */
void test() {

	SYSCALL(VERHOGEN, (int)&testsem, 0, 0);					/* V(testsem)   */

	print("p1 v(testsem)\n");

	/* set up states of the other processes */

	/* set up p2's state */
	STST(&p2state);			/* create a state area             */

	p2state.s_sp = p2state.s_sp - QPAGE;			/* stack of p2 should sit above    */
	p2state.s_pc = p2state.s_t9 = (memaddr)p2;		/* p2 starts executing function p2 */
	p2state.s_status = p2state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;


	STST(&p3state);

	p3state.s_sp = p2state.s_sp - QPAGE;
	p3state.s_pc = p3state.s_t9 = (memaddr)p3;
	p3state.s_status = p3state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;


	STST(&p4state);

	p4state.s_sp = p3state.s_sp - QPAGE;
	p4state.s_pc = p4state.s_t9 = (memaddr)p4;
	p4state.s_status = p4state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;


	STST(&p5state);

	p5Stack = p5state.s_sp = p4state.s_sp - (2 * QPAGE);	/* because there will 2 p4 running*/
	p5state.s_pc = p5state.s_t9 = (memaddr)p5;
	p5state.s_status = p5state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&p6state);

	p6state.s_sp = p5state.s_sp - (2 * QPAGE);
	p6state.s_pc = p6state.s_t9 = (memaddr)p6;
	p6state.s_status = p6state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;


	STST(&p7state);

	p7state.s_sp = p6state.s_sp - QPAGE;
	p7state.s_pc = p7state.s_t9 = (memaddr)p7;
	p7state.s_status = p7state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&p8rootstate);
	p8rootstate.s_sp = p7state.s_sp - QPAGE;
	p8rootstate.s_pc = p8rootstate.s_t9 = (memaddr)p8root;
	p8rootstate.s_status = p8rootstate.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&child1state);
	child1state.s_sp = p8rootstate.s_sp - QPAGE;
	child1state.s_pc = child1state.s_t9 = (memaddr)child1;
	child1state.s_status = child1state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&child2state);
	child2state.s_sp = child1state.s_sp - QPAGE;
	child2state.s_pc = child2state.s_t9 = (memaddr)child2;
	child2state.s_status = child2state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&gchild1state);
	gchild1state.s_sp = child2state.s_sp - QPAGE;
	gchild1state.s_pc = gchild1state.s_t9 = (memaddr)p8leaf;
	gchild1state.s_status = gchild1state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&gchild2state);
	gchild2state.s_sp = gchild1state.s_sp - QPAGE;
	gchild2state.s_pc = gchild2state.s_t9 = (memaddr)p8leaf;
	gchild2state.s_status = gchild2state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&gchild3state);
	gchild3state.s_sp = gchild2state.s_sp - QPAGE;
	gchild3state.s_pc = gchild3state.s_t9 = (memaddr)p8leaf;
	gchild3state.s_status = gchild3state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	STST(&gchild4state);
	gchild4state.s_sp = gchild3state.s_sp - QPAGE;
	gchild4state.s_pc = gchild4state.s_t9 = (memaddr)p8leaf;
	gchild4state.s_status = gchild4state.s_status | IEPBITON | CAUSEINTMASK | TEBITON;

	/* create process p2 */
	SYSCALL(CREATETHREAD, (int)&p2state, (int) NULL , 0);				/* start p2     */

	print("p2 was started\n");

	SYSCALL(VERHOGEN, (int)&startp2, 0, 0);					/* V(startp2)   */

	SYSCALL(PASSERN, (int)&endp2, 0, 0);					/* P(endp2)     */

	/* make sure we really blocked */
	if (p1p2synch == 0)
		print("error: p1/p2 synchronization bad\n");

	SYSCALL(CREATETHREAD, (int)&p3state, (int) NULL, 0);				/* start p3     */

	print("p3 is started\n");

	SYSCALL(PASSERN, (int)&endp3, 0, 0);					/* P(endp3)     */

	SYSCALL(CREATETHREAD, (int)&p4state, (int) NULL, 0);				/* start p4     */

	pFiveSupport.sup_exceptContext[GENERALEXCEPT].c_stackPtr = (int) p5Stack;
/*	pFiveSupport.sup_exceptContext[GENERALEXCEPT].c_stackPtr = (int) &(pFiveSupport.sup_stackGen[500]); */
	pFiveSupport.sup_exceptContext[GENERALEXCEPT].c_status = ALLOFF | IEPBITON | CAUSEINTMASK | TEBITON;
	pFiveSupport.sup_exceptContext[GENERALEXCEPT].c_pc =  (memaddr) p5gen;
	pFiveSupport.sup_exceptContext[PGFAULTEXCEPT].c_stackPtr = p5Stack;
/*	pFiveSupport.sup_exceptContext[PGFAULTEXCEPT].c_stackPtr = &(pFiveSupport.sup_stackMM[500]); */
	pFiveSupport.sup_exceptContext[PGFAULTEXCEPT].c_status = ALLOFF | IEPBITON | CAUSEINTMASK | TEBITON;
	pFiveSupport.sup_exceptContext[PGFAULTEXCEPT].c_pc =  (memaddr) p5mm;

	SYSCALL(CREATETHREAD, (int)&p5state, (int) &(pFiveSupport), 0); 			/* start p5     */

	SYSCALL(CREATETHREAD, (int)&p6state, (int) NULL, 0);				/* start p6		*/

	SYSCALL(CREATETHREAD, (int)&p7state, (int) NULL, 0);				/* start p7		*/

	SYSCALL(PASSERN, (int)&endp5, 0, 0);					/* P(endp5)		*/

	print("p1 knows p5 ended\n");

	SYSCALL(PASSERN, (int)&blkp4, 0, 0);					/* P(blkp4)		*/

	/* now for a more rigorous check of process termination */
	for (p8inc=0; p8inc<4; p8inc++) {
		creation = SYSCALL(CREATETHREAD, (int)&p8rootstate, (int) NULL, 0);

		if (creation == CREATENOGOOD) {
			print("error in process termination\n");
			PANIC();
		}

		SYSCALL(PASSERN, (int)&endp8, 0, 0);
	}

	print("p1 finishes OK -- TTFN\n");
	* ((memaddr *) BADADDR) = 0;				/* terminate p1 */

	/* should not reach this point, since p1 just got a program trap */
	print("error: p1 still alive after progtrap & no trap vector\n");
	PANIC();					/* PANIC !!!     */
}


/* p2 -- semaphore and cputime-SYS test process */
void p2() {
	int		i;				/* just to waste time  */
	cpu_t	now1,now2;		/* times of day        */
	cpu_t	cpu_t1,cpu_t2;	/* cpu time used       */

	SYSCALL(PASSERN, (int)&startp2, 0, 0);				/* P(startp2)   */

	print("p2 starts\n");

	/* initialize all semaphores in the s[] array */
	for (i=0; i<= MAXSEM; i++)
		s[i] = 0;

	/* V, then P, all of the semaphores in the s[] array */
	for (i=0; i<= MAXSEM; i++)  {
		SYSCALL(VERHOGEN, (int)&s[i], 0, 0);			/* V(S[I]) */
		SYSCALL(PASSERN, (int)&s[i], 0, 0);			/* P(S[I]) */
		if (s[i] != 0)
			print("error: p2 bad v/p pairs\n");
	}

	print("p2 v's successfully\n");

	/* test of SYS6 */

	STCK(now1);				/* time of day   */
	cpu_t1 = SYSCALL(GETCPUTIME, 0, 0, 0);			/* CPU time used */

	/* delay for several milliseconds */
	for (i=1; i < LOOPNUM; i++)
		;

	cpu_t2 = SYSCALL(GETCPUTIME, 0, 0, 0);			/* CPU time used */
	STCK(now2);				/* time of day  */

	if (((now2 - now1) >= (cpu_t2 - cpu_t1)) &&
			((cpu_t2 - cpu_t1) >= (MINLOOPTIME / (* ((cpu_t *)TIMESCALEADDR)))))
		print("p2 is OK\n");
	else  {
		if ((now2 - now1) < (cpu_t2 - cpu_t1))
			print ("error: more cpu time than real time\n");
		if ((cpu_t2 - cpu_t1) < (MINLOOPTIME / (* ((cpu_t *)TIMESCALEADDR))))
			print ("error: not enough cpu time went by\n");
		print("p2 blew it!\n");
	}

	p1p2synch = 1;				/* p1 will check this */

	SYSCALL(VERHOGEN, (int)&endp2, 0, 0);				/* V(endp2)     */

	SYSCALL(TERMINATETHREAD, 0, 0, 0);			/* terminate p2 */

	/* just did a SYS2, so should not get to this point */
	print("error: p2 didn't terminate\n");
	PANIC();					/* PANIC!           */
}


/* p3 -- clock semaphore test process */
void p3() {
	cpu_t	time1, time2;
	cpu_t	cpu_t1,cpu_t2;		/* cpu time used       */
	int		i;

	time1 = 0;
	time2 = 0;

	/* loop until we are delayed at least half of clock V interval */
	while (time2-time1 < (CLOCKINTERVAL >> 1) )  {
		STCK(time1);			/* time of day     */
		SYSCALL(WAITCLOCK, 0, 0, 0);
		STCK(time2);			/* new time of day */
	}

	print("p3 - WAITCLOCK OK\n");

	/* now let's check to see if we're really charge for CPU
	   time correctly */
	cpu_t1 = SYSCALL(GETCPUTIME, 0, 0, 0);

	for (i=0; i<CLOCKLOOP; i++)
		SYSCALL(WAITCLOCK, 0, 0, 0);

	cpu_t2 = SYSCALL(GETCPUTIME, 0, 0, 0);

	if (cpu_t2 - cpu_t1 < (MINCLOCKLOOP / (* ((cpu_t *) TIMESCALEADDR))))
		print("error: p3 - CPU time incorrectly maintained\n");
	else
		print("p3 - CPU time correctly maintained\n");


	SYSCALL(VERHOGEN, (int)&endp3, 0, 0);				/* V(endp3)        */

	SYSCALL(TERMINATETHREAD, 0, 0, 0);			/* terminate p3    */

	/* just did a SYS2, so should not get to this point */
	print("error: p3 didn't terminate\n");
	PANIC();					/* PANIC            */
}


/* p4 -- termination test process */
void p4() {
	switch (p4inc) {
		case 1:
			print("first incarnation of p4 starts\n");
			p4inc++;
			break;
		case 2:
			print("second incarnation of p4 starts\n");
			break;
	}

	SYSCALL(VERHOGEN, (int)&synp4, 0, 0);				/* V(synp4)     */

	SYSCALL(PASSERN, (int)&blkp4, 0, 0);				/* P(blkp4)     */

	SYSCALL(PASSERN, (int)&synp4, 0, 0);				/* P(synp4)     */

	/* start another incarnation of p4 running, and wait for  */
	/* a V(synp4). the new process will block at the P(blkp4),*/
	/* and eventually, the parent p4 will terminate, killing  */
	/* off both p4's.                                         */

	p4state.s_sp -= QPAGE;		/* give another page  */

	SYSCALL(CREATETHREAD, (int)&p4state, 0, 0);			/* start a new p4    */

	SYSCALL(PASSERN, (int)&synp4, 0, 0);				/* wait for it       */

	print("p4 is OK\n");

	SYSCALL(VERHOGEN, (int)&endp4, 0, 0);				/* V(endp4)          */

	SYSCALL(TERMINATETHREAD, 0, 0, 0);			/* terminate p4      */

	/* just did a SYS2, so should not get to this point */
	print("error: p4 didn't terminate\n");
	PANIC();					/* PANIC            */
}



/* p5's program trap handler */
void p5gen() {
	unsigned int exeCode = pFiveSupport.sup_exceptState[GENERALEXCEPT].s_cause;
	exeCode = (exeCode & CAUSEMASK) >> 2;
	switch (exeCode) {
	case BUSERROR:
		print("Bus Error: Access non-existent memory\n");
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_pc = (memaddr)p5a;   /* Continue with p5a() */
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_t9 = (memaddr)p5a;   /* Continue with p5a() */
		break;

	case RESVINSTR:
		print("privileged instruction\n");
		/* return in kernel mode */
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_pc = (memaddr)p5b;   /* Continue with p5b() */
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_t9 = (memaddr)p5b;   /* Continue with p5b() */
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_status = pFiveSupport.sup_exceptState[GENERALEXCEPT].s_status & KUPBITOFF;
		break;

	case ADDRERROR:
		print("Address Error: non-kuseg access w/KU=1\n");
		/* return in kernel mode */
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_pc = (memaddr)p5b;   /* Continue with p5b() */
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_t9 = (memaddr)p5b;   /* Continue with p5b() */
		pFiveSupport.sup_exceptState[GENERALEXCEPT].s_status = pFiveSupport.sup_exceptState[GENERALEXCEPT].s_status & KUPBITOFF;
		break;

	case SYSCALLEXCPT:
		p5sys();
		break;

	default:
		print("other program trap\n");
	}

	LDST(&(pFiveSupport.sup_exceptState[GENERALEXCEPT]));
}

/* p5's memory management trap handler */
void p5mm() {
	print("memory management trap\n");

	support_t* pFiveSupAddr = (support_t *)SYSCALL(GETSPTPTR, 0, 0, 0);
	if ((pFiveSupAddr) != &(pFiveSupport)) {
		print("Support Structure Address Error\n");
	} else{
		print("Correct Support Structure Address\n");
	}

	pFiveSupport.sup_exceptState[PGFAULTEXCEPT].s_status = pFiveSupport.sup_exceptState[PGFAULTEXCEPT].s_status | KUPBITON;	/* user mode on 	*/
	pFiveSupport.sup_exceptState[PGFAULTEXCEPT].s_pc = (memaddr)p5b;   										/* return to p5b()	*/
	pFiveSupport.sup_exceptState[PGFAULTEXCEPT].s_t9 = (memaddr)p5b;											/* return to p5b()	*/

	LDST(&(pFiveSupport.sup_exceptState[PGFAULTEXCEPT]));
}

/* p5's SYS trap handler */
void p5sys() {
	unsigned int p5status = pFiveSupport.sup_exceptState[GENERALEXCEPT].s_status;
	p5status = (p5status << 28) >> 31;
	switch(p5status) {
	case ON:
		print("High level SYS call from user mode process\n");
		break;

	case OFF:
		print("High level SYS call from kernel mode process\n");
		break;
	}
	pFiveSupport.sup_exceptState[GENERALEXCEPT].s_pc = pFiveSupport.sup_exceptState[GENERALEXCEPT].s_pc + 4;   /*	 to avoid SYS looping */
	LDST(&(pFiveSupport.sup_exceptState[GENERALEXCEPT]));
}

/* p5 -- SYS5 test process */
void p5() {
	print("p5 starts\n");

	/* cause a pgm trap access some non-existent memory */
	*p5MemLocation = *p5MemLocation + 1;		 /* Should cause a program trap */
}

void p5a() {
	unsigned int p5Status;

	/* generage a TLB exception after a TLB-Refill event */

	p5MemLocation = (memaddr) 0x80000000;
	*p5MemLocation = 42;
}

/* second part of p5 - should be entered in user mode first time through */
/* should generate a program trap (Address error) */
void p5b() {
	cpu_t		time1, time2;

	SYSCALL(9, 0, 0, 0);
	SYSCALL(PASSERN, (int)&endp4, 0, 0);			/* P(endp4)*/

	/* do some delay to be reasonably sure p4 and its offspring are dead */
	time1 = 0;
	time2 = 0;
	while (time2 - time1 < (CLOCKINTERVAL >> 1))  {
		STCK(time1);
		SYSCALL(WAITCLOCK, 0, 0, 0);
		STCK(time2);
	}

	/* if p4 and offspring are really dead, this will increment blkp4 */

	SYSCALL(VERHOGEN, (int)&blkp4, 0, 0);			/* V(blkp4) */

	SYSCALL(VERHOGEN, (int)&endp5, 0, 0);			/* V(endp5) */

	/* should cause a termination       */
	/* since this has already been      */
	/* done for PROGTRAPs               */

	/*
	SYSCALL(SPECTRAPVEC, PROGTRAP, (int)&pstat_o, (int)&pstat_n);
	*/

	SYSCALL(TERMINATETHREAD, 0, 0, 0);

	/* should have terminated, so should not get to this point */
	print("error: p5 didn't terminate\n");
	PANIC();				/* PANIC            */
}


/*p6 -- high level syscall without initializing passup vector */
void p6() {
	print("p6 starts\n");

	SYSCALL(9, 0, 0, 0);		/* should cause termination because p6 has no
			  trap vector */

	print("error: p6 alive after SYS9() with no trap vector\n");

	PANIC();
}

/*p7 -- program trap without initializing passup vector */
void p7() {
	print("p7 starts\n");

	* ((memaddr *) BADADDR) = 0;

	print("error: p7 alive after program trap with no trap vector\n");
	PANIC();
}


/* p8root -- test of termination of subtree of processes              */
/* create a subtree of processes, wait for the leaves to block, signal*/
/* the root process, and then terminate                               */
void p8root() {
	int		grandchild;

	print("p8root starts\n");

	SYSCALL(CREATETHREAD, (int)&child1state, (int) NULL, 0);

	SYSCALL(CREATETHREAD, (int)&child2state, (int) NULL, 0);

	for (grandchild=0; grandchild < NOLEAVES; grandchild++) {
		SYSCALL(PASSERN, (int)&endcreate, 0, 0);
	}

	SYSCALL(VERHOGEN, (int)&endp8, 0, 0);

	SYSCALL(TERMINATETHREAD, 0, 0, 0);
}

/*child1 & child2 -- create two sub-processes each*/

void child1() {
	print("child1 starts\n");

	SYSCALL(CREATETHREAD, (int)&gchild1state, (int) NULL, 0);

	SYSCALL(CREATETHREAD, (int)&gchild2state, (int) NULL, 0);

	SYSCALL(PASSERN, (int)&blkp8, 0, 0);
}

void child2() {
	print("child2 starts\n");

	SYSCALL(CREATETHREAD, (int)&gchild3state, (int) NULL, 0);

	SYSCALL(CREATETHREAD, (int)&gchild4state, (int) NULL, 0);

	SYSCALL(PASSERN, (int)&blkp8, 0, 0);
}

/*p8leaf -- code for leaf processes*/

void p8leaf() {
	print("leaf process starts\n");

	SYSCALL(VERHOGEN, (int)&endcreate, 0, 0);

	SYSCALL(PASSERN, (int)&blkp8, 0, 0);
}
