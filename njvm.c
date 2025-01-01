#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <bigint.h>
#include <support.h>

#define STACK_SIZE 10000

#define IMMEDIATE(x) ((x)&0x00FFFFFF)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))
#define MSB (1 << (8 * sizeof(unsigned int) - 1)) 
#define IS_PRIMITIVE(objRef) (((objRef)->size & MSB) == 0) 
#define GET_ELEMENT_COUNT(objRef) ((objRef)->size & ~MSB)
#define GET_REFS_PTR(objRef) ((ObjRef *) (objRef)->data)

#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10
#define PUSHG 11
#define POPG 12
#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16
#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22
#define JMP 23
#define BRF 24
#define BRT 25
#define CALL 26
#define RET 27 
#define DROP 28 
#define PUSHR 29 
#define POPR 30 
#define DUP 31
#define NEW 32 
#define GETF 33
#define PUTF 34 
#define NEWA 35 
#define GETFA 36 
#define PUTFA 37 
#define GETSZ 38 
#define PUSHN 39
#define REFEQ 40 
#define REFNE 41 


typedef enum
{
    false,
    true
} bool;

#if 0 
typedef struct
{
    unsigned int size; 
    // # byte of payload
    unsigned char data[1]; 
    // payload data, size as needed!
    } *ObjRef;
#endif
    typedef struct
    {
        bool isobjref;

        union
        {
            int number;
            ObjRef objref;
        } u;

    } Stackslot;
    int point;
    Stackslot stack[STACK_SIZE];
    int sp = 0;
    int fp = 0;
    int pc = 0;
    int string_pc = 0;
    ObjRef *sda;
    ObjRef rvr;
    uint32_t instruction_toexecute;
uint32_t prog1[] =
    {
        (PUSHC << 24) | IMMEDIATE(3),
        (PUSHC << 24) | IMMEDIATE(4),
        ADD << 24,
        (PUSHC << 24) | IMMEDIATE(10),
        (PUSHC << 24) | IMMEDIATE(6),
        SUB << 24,
        DIV << 24,
        WRINT << 24,
        (PUSHC << 24) | IMMEDIATE(10),
        WRCHR << 24,
        HALT};

ObjRef newPrimObject(int dataSize) {
  ObjRef objRef;

  objRef = malloc(sizeof(unsigned int) + dataSize * sizeof(unsigned char));
  if (objRef == NULL) {
    fatalError("newPrimObject() got no memory");
  }
  objRef->size = dataSize;
  return objRef;
}
void fatalError(char *msg) {
  printf("Fatal error: %s\n", msg);
  exit(1);
}

void print_stack(void)
{
    printf("\n     Stack\n");
    printf(".-------+--------.\n");
    for (int i = sp; i >= 0; i--)
    {
        if (i == sp)
            printf("|sp->%3d| <empty>|\n", i);
        else
            printf("|%7d|  0x%02hhx |\n", i, stack[i].u.objref);
    }
    printf("'-------+--------'\n\n");
}



void pushc(int x)
{
    /* das alles übernimmt big int lib mit dem newprimobjekt funktion 
ObjRef intobject ;
 
 if ((intobject = malloc(sizeof(int)+sizeof(unsigned int))) == NULL)
    {
        perror("malloc");
    }
    intobject->size=sizeof(int);
        *(int *)intobject->data=x;

    */
    

    if (sp == STACK_SIZE)
    {
        printf("stack overflow \n");
        exit(1);
    }
    else
    {
        bigFromInt(x);
        stack[sp].isobjref= true;
        stack[sp].u.objref=bip.res;
        sp++;
     
    }
}
void pushob(ObjRef obref ){
if (sp == STACK_SIZE)
    {
        fatalError("stack overflow \n");
        exit(1);
    }
    else
    {
        stack[sp].isobjref= true;
        stack[sp].u.objref=obref;
        sp++;
     
    }

}

void pushnum(int x)
{


    if (sp == STACK_SIZE)
    {
        printf("stack overflow \n");
        exit(1);
    }
    else
    {
        stack[sp].isobjref= false;
        stack[sp].u.number=x;
        sp++;
    }
}

int pop()
{
    int value;
    if (sp > 0)
    {
        if(stack[sp-1].isobjref==false){
            value=stack[sp-1].u.number;
        }
        else{
        value = *(int *)stack[sp - 1].u.objref->data;
        }
        sp--;
        return value;
        printf("this was reached \n");
    }
    else
    {
        printf("the stack is empty -> 'underflow case' \n");
        exit(1);
    }
}
ObjRef popref()
{
    ObjRef value;
    if (sp > 0)
    {
        value = stack[sp - 1].u.objref;
        sp--;
        return value;
        printf("this was reached \n");
    }
    else
    {
        printf("the stack is empty -> 'underflow case' \n");
        exit(1);
    }
}


void halt(void)
{
    exit(0);
}

void add(void)
{
    bip.op1=popref();
    bip.op2=popref();
    bigAdd();
    pushob(bip.res);
}
void sub(void)
{
    bip.op2=popref();
    bip.op1=popref();
    
    bigSub();
    pushob(bip.res);
}
void mul(void)
{
     bip.op1=popref();
    bip.op2=popref();
    bigMul();
    pushob(bip.res);
}
void divide(void)
{
     bip.op2=popref();
     bip.op1=popref();
    
    
   
  
        bigDiv();
        pushob(bip.res);
    
}
void mod(void)
{
    bip.op2=popref();
     bip.op1=popref();
    
 
   
        bigDiv();
        pushob(bip.rem);
    
}
void rdint(void)
{
    /*
    int value;
    scanf("%d", &value);
    */
    bigRead(stdin);
    pushob(bip.res);
}
void wrint(void)
{
 //   printf("%d", pop());
bip.op1=popref();
 bigPrint(stdout);

}
void rdchr(void)
{
    char chr;
    scanf("%c", &chr);
    int zahl ; 
    zahl=(int)chr;
    bigFromInt(zahl);
    pushob(bip.res);
}
void wrchr(void)
{
int zahl ; 
bip.op1=popref();
zahl=bigToInt();
    printf("%c", zahl);
}

void pushg(int n)
{
    //pushc( *(int *)sda[n]->data);
    pushob(sda[n]);
}
void popg(int n)
{
    sda[n] = popref();
}
void asf(int n)
{
    pushnum(fp);
    fp = sp;
    sp = sp + n;
    for(int i=fp;i<sp;i++){
        stack[i].isobjref=true;
    }
}
void rsf(void)
{
    sp = fp;
    fp = pop();
}
void pushl(int n)
{
  //  pushc( *(int *)stack[fp + n].u.objref->data);
  pushob(stack[fp+n].u.objref);
}
void popl(int n)
{
    stack[fp + n].u.objref = popref();
}
void equal(void)
{
    int res ;
    bip.op1=popref();
    bip.op2=popref();
    res= bigCmp();
    if (res==0)
    {
        pushc(true);
    }
    else
    {
        pushc(false);
    }
}
void notequal(void)
{
    int res ;
    bip.op1=popref();
    bip.op2=popref();
    res= bigCmp();
    if (res!=0)
    {
        pushc(true);
    }
    else
    {
        pushc(false);
    }
}
void lessthan(void)
{
    /*
    int val1 = pop();
    int val2 = pop();
    if (val2 < val1)
    {
        pushc(true);
    }
    else
    {
        pushc(false);
    }
    */
    int res ;
    bip.op2=popref();
    bip.op1=popref();
    res= bigCmp();
    if (res<0)
    {
        pushc(true);
    }
    else
    {
        pushc(false);
    }
}
void lessequal(void)
{
    int res ;
    bip.op2=popref();
    bip.op1=popref();
    res= bigCmp();
    if ( (res<0)||(res==0) )
    {
        pushc(true);
    }
    else
    {
        pushc(false);
    }
}
void greaterthan(void){
     int res ;
    bip.op2=popref();
    bip.op1=popref();
    res= bigCmp();
    if(res>0){
        pushc(true);
    }
    else{
        pushc(false);
    }
}

void greaterequal(void){
     int res ;
    bip.op2=popref();
    bip.op1=popref();
    res= bigCmp();
    if((res>0)||(res==0)){
        pushc(true);
    }
    else{
        pushc(false);
    }
}
void jump(int target){
    pc=target ;
}
void branchonfalse(int target){
if(pop()==false){
 pc=target ; 
}

}
void branchontrue(int target){
if(pop()==true){
 pc=target ; 
}

}
void call (int target ){
pushnum(pc);
pc = target ;
}
void ret(void){
    pc=pop();
}
void drop(int n){ 
    for(int i=0; i<n;i++){
        popref();
    }
}
void pushr(void){
  //  pushc( *(int *)rvr->data);
  pushob(rvr);
}
void popr(void){
    rvr=popref();
}
void dup (void){
    
  //  pushc(*(int *)stack[sp-1].u.objref->data);
  pushob(stack[sp-1].u.objref);
} 
void new (int n ){
int x ; 
x= n | MSB ;                                                                                                                                                                                                                            
ObjRef objRef;

  objRef = (ObjRef )malloc(sizeof(* objRef ) +  n * sizeof(void *));
  if (objRef == NULL) {
    fatalError("objref() got no memory");
  }
  (*objRef).size = x;
  printf("get size of objref %d \n",objRef->size & ~MSB);
    printf("get size of objref %d \n",((ObjRef *) (objRef)->size)[1] );


  
  /*
  for(int i =0;i<n;i++){
      GET_REFS_PTR(objRef)[i]=NULL;
  }
  */
  pushob(objRef);
}
void getfield(int i){
ObjRef object = popref();
ObjRef valueref =GET_REFS_PTR(object)[i];
pushob(valueref);
//printf(" -%03d- test hier getf\n",pc);

}
void putfield(int i){
    ObjRef value = popref(); 
    ObjRef object = popref();
  //  GET_REFS_PTR(object)[i]=malloc(8);
    //GET_REFS_PTR(object)[i]->size= sizeof(ObjRef);
   GET_REFS_PTR(object)[i] = value ;
//printf("-%03d test hier putf\n",pc);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
void newa (void){
  bip.op1= popref(); 
//ObjRef nelem =popref(); number of elements in array                                                                                                                                                                                                                           
 //int indices = *(int*)nelem->data;
 int indices=bigToInt();
ObjRef array =(ObjRef ) malloc(indices * sizeof(ObjRef *));
if (array == NULL) {
    fatalError("objref() got no memory");
  }
  array->size=indices | MSB;

  /*
for(int i=0;i<indices;i++){
    GET_REFS_PTR(array)[i]=NULL;
}
*/
  pushob(array);
  
}
void putfieldarray (void) {

ObjRef value= popref();
bip.op1 =popref();//index 
int index = bigToInt(); 
ObjRef array=popref();

GET_REFS_PTR(array)[index]=value;

}
void getfieldarray(void){
bip.op1 = popref();//index
int index=bigToInt();
ObjRef array =popref();
pushob(GET_REFS_PTR(array)[index]);
}

void getsz (void) {
    ObjRef object=popref();
if( IS_PRIMITIVE ( object ) ){
pushc(-1);
}
else{
pushc( GET_ELEMENT_COUNT(object) );
}

}

void pushn(void){

pushob(NULL);

}

void refeq(void){
  ObjRef  op1 =popref();
    ObjRef op2 = popref();
    
    if(op1==op2){
        pushc(true);
    }
    else{
        pushc(false);
    }
}
void refne(void){
    ObjRef  op1 =popref();
    ObjRef op2 = popref();
    if(op1!=op2){
        pushc(true);
    }
    else{
        pushc(false);
    }
}
void tostring(uint32_t instruction)
{

    uint32_t opcode;
    opcode = instruction >> 24;

    if (opcode == PUSHC)
    {

        printf("%03d:pushc\t %d \n", string_pc, (SIGN_EXTEND(instruction & 0x00FFFFFF)));
    }
    if (opcode == ADD)
    {

        printf("%03d:add\n", string_pc);
    }

    if (opcode == SUB)
    {

        printf("%03d:sub\n", string_pc);
    }

    if (opcode == MUL)
    {

        printf("%03d:mul\n", string_pc);
    }
    if (opcode == DIV)
    {
        printf("%03d:div\n", string_pc);
    }
    if (opcode == MOD)
    {
        printf("%03d:mod\n", string_pc);
    }
    if (opcode == RDINT)
    {
        printf("%03d:rdint\n", string_pc);
    }
    if (opcode == WRINT)
    {

        printf("%03d:wrint\n", string_pc);
    }
    if (opcode == RDCHR)
    {
        printf("%03d:rdchr\n", string_pc);
    }
    if (opcode == WRCHR)
    {
        printf("%03d:wrchr\n", string_pc);
    }
    if (opcode == PUSHG)
    {
        printf("%03d:pushg\t %d \n", string_pc, (SIGN_EXTEND(instruction & 0x00FFFFFF)));
    }
    if (opcode == POPG)
    {
        printf("%03d:popg\t %d \n", string_pc, (SIGN_EXTEND(instruction & 0x00FFFFFF)));
    }
    if (opcode == ASF)
    {
        printf("%03d:asf\t %d \n", string_pc, (SIGN_EXTEND(instruction & 0x00FFFFFF)));
    }
    if (opcode == RSF)
    {
        printf("%03d:rsf\t\n", string_pc);
    }
    if (opcode == PUSHL)
    {
        printf("%03d:pushl\t %d \n", string_pc, (SIGN_EXTEND(instruction & 0x00FFFFFF)));
    }
    if (opcode == POPL)
    {
        printf("%03d:popl\t %d \n", string_pc, (SIGN_EXTEND(instruction & 0x00FFFFFF)));
    }
    if (opcode == EQ)
    {
        printf("%03d:eq\n", string_pc);
    }
    if (opcode == NE)
    {
        printf("%03d:ne\n", string_pc);
    }
    if (opcode == LT)
    {
        printf("%03d:lt\n", string_pc);
    }
    if (opcode == LE)
    {
        printf("%03d:le\n", string_pc);
    }
    if (opcode == GT)
    {
        printf("%03d:gt\n", string_pc);
    }
    if (opcode == GE)
    {
        printf("%03d:ge\n", string_pc);
    }
    if (opcode == JMP)
    {
        printf("%03d:JMP\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == BRF)
    {
        printf("%03d:brf\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == BRT)
    {
        printf("%03d:brt\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == CALL)
    {
        printf("%03d:call\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == RET)
    {
        printf("%03d:ret\n", string_pc);
    }
    if (opcode == DROP)
    {
        printf("%03d:drop\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == PUSHR)
    {
        printf("%03d:pushr\n", string_pc);
    }
    if (opcode == POPR)
    {
        printf("%03d:popr\n", string_pc);
    }
    if (opcode == DUP)
    {
        printf("%03d:dup\n", string_pc);
    }
    if (opcode == NEW)
    {
        printf("%03d:new\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == GETF)
    {
        printf("%03d:getf\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == PUTF)
    {
        printf("%03d:putf\t %d \n", string_pc,SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if (opcode == NEWA)
    {
        printf("%03d:newa\n", string_pc);
    }
    if (opcode == PUTFA)
    {
        printf("%03d:putfa\n", string_pc);
    }
    if (opcode == GETFA)
    {
        printf("%03d:getfa\n", string_pc);
    }
    if (opcode == GETSZ)
    {
        printf("%03d:getsz\n", string_pc);
    }
    if (opcode == PUSHN)
    {
        printf("%03d:pushn\n", string_pc);
    }
    if (opcode == REFEQ)
    {
        printf("%03d:refeq\n", string_pc);
    }
    if (opcode == REFNE)
    {
        printf("%03d:refne\n", string_pc);
    }

}

void execute(uint32_t instruction)
{

    if ((instruction >> 24) == PUSHC)
    {

        pushc(SIGN_EXTEND(instruction & 0x00FFFFFF));
    }
    if ((instruction >> 24) == ADD)
    {
        add();
    }
    if ((instruction >> 24) == SUB)
    {
        sub();
    }
    if ((instruction >> 24) == MUL)
    {
        mul();
    }
    if ((instruction >> 24) == DIV)
    {
        divide();
    }
    if ((instruction >> 24) == MOD)
    {
        mod();
    }
    if ((instruction >> 24) == RDINT)
    {
        rdint();
    }
    if ((instruction >> 24) == WRINT)
    {
        wrint();
    }
    if ((instruction >> 24) == RDCHR)
    {
        rdchr();
    }
    if ((instruction >> 24) == WRCHR)
    {
        wrchr();
    }
    if ((instruction >> 24) == PUSHG)
    {
        pushg(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == POPG)
    {
        popg(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == ASF)
    {
        asf(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == RSF)
    {
        rsf();
    }
    if ((instruction >> 24) == PUSHL)
    {
        pushl(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == POPL)
    {
        popl(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == EQ)
    {
        equal();
    }
    if ((instruction >> 24) == NE)
    {
        notequal();
    }
    if ((instruction >> 24) == LT)
    {
        lessthan();
    }
    if ((instruction >> 24) == LE)
    {
        lessequal();
    }
    if ((instruction >> 24) == GT)
    {
        greaterthan();
    }
    if ((instruction >> 24) == GE)
    {
        greaterequal();
    }
    if ((instruction >> 24) == JMP)
    {
        jump(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == BRF)
    {
        branchonfalse(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == BRT)
    {
        branchontrue(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == CALL)
    {
        call(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == RET)
    {
        ret();
    }
    if ((instruction >> 24) == DROP)
    {
        drop(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == PUSHR)
    {
        pushr();
    }
    if ((instruction >> 24) == POPR)
    {
        popr();
    }
    if ((instruction >> 24) == DUP)
    {
        dup();
    }
    if ((instruction >> 24) == NEW)
    {
        new(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == PUTF)
    {
        putfield(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == GETF)
    {
        getfield(SIGN_EXTEND(IMMEDIATE(instruction)));
    }
    if ((instruction >> 24) == NEWA)
    {
        newa();
    }
    if ((instruction >> 24) == GETFA)
    {
        getfieldarray();
    }
    if ((instruction >> 24) == PUTFA)
    {
        putfieldarray();
    }
    if ((instruction >> 24) == GETSZ)
    {
        getsz();
    }
    if ((instruction >> 24) == PUSHN)
    {
        pushn();
    }
    if ((instruction >> 24) == REFEQ)
    {
        refeq();
    }
    if ((instruction >> 24) == REFNE)
    {
        refne();
    }
    
}

int main(int argc, char *argv[])
{
    int inst; //single instruction

    int format; //njbf
    int version;
    int instructions_num; // number of instructions
    int static_vars;      // number of variables in the static data area (global variables)
    int i;
    int inst_counter = 0;
    FILE *filep = NULL;

#if 0
    unsigned int items[]={2,4,8,16,32,64,128, 256, 512, 1024};

    for(i=0;i<sizeof(items)/sizeof(items[0]);i++){
   
        printf("the pointers %p -> value : %d\n \n",(void *)(items+i),*(items+i));
                printf("the items %p -> value : %d\n \n",(void *)(&items[0]+i),*(items+i));

            printf("the pointers %p -> value : %d\n \n",(void *)&items[i],*(items+i));



    }
#endif
    // AUSGABE: "r 4 bytes: c = [A, B, C, D]"

    printf("Ninja Virtual Machine started\n");
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--h") == 0)
    {
        printf("usage: ./njvm [option] [option] ...\n --version        show version and exit \n --help           show this help and exit \n");
    }
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "--v") == 0)
    {
        printf("Ninja Virtual Machine version 2 (compiled Sep 23 2015, 10:36:52)\n");
    }
    if (strcmp(argv[1], "--help") != 0 && strcmp(argv[1], "--h") != 0 && strcmp(argv[1], "--version") != 0 && strcmp(argv[1], "--v") != 0 && (strstr(argv[1], ".bin") == NULL))
    {
        printf("unknown command line argument '%s' , try './njvm --help'\n", argv[1]);
    }
    
    if(argc==3){
    if ( strstr(argv[1], ".bin") != NULL && strcmp(argv[2],"--d")==0){
           if ((filep = fopen(argv[1], "r")) == NULL)
        {
            perror("ERROR - fopen");
            exit(1);
        }
        fread(&format, sizeof(int), 1, filep); //read njbf
        if (format != 1178749518)
        {
            printf("this is not a ninja binary file \n");
            exit(1);
        }
        fread(&version, sizeof(int), 1, filep);          //read version
        fread(&instructions_num, sizeof(int), 1, filep); //read instructions
        fread(&static_vars, sizeof(int), 1, filep);      //num of global variables
        sda = malloc(static_vars * sizeof(ObjRef));
        int anweisungen[instructions_num];
       
        while ((fread(&inst, sizeof(int), 1, filep)) == 1)
        {
            anweisungen[inst_counter] = inst;
            inst_counter++;
        }
        fclose(filep);
        for (i = 0; i < sizeof(anweisungen) / sizeof(anweisungen[0]); i++)
        {
            printf("%x ", anweisungen[i]);
        }
        puts("");
         options :
         printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
         char choice[10]; 
         while(strcmp(choice,"q")!=0){
             
        scanf("%s",choice); 
       
       if(strcmp(choice,"q")==0){
               printf("Ninja Virtual Machine ended\n");
            exit(0);
            }

        if(strcmp(choice,"b")==0){
           if(point==NULL){
           printf("DEBUG [breakpoint]: cleared\n");
           }
           else{
          printf("DEBUG [breakpoint]: %d\n",point);
            }
        printf("DEBUG [breakpoint]: address to set, -1 to clear, <-9> for no change?\n");
           int bp ;
            scanf("%d",&bp);
            if(bp!=-9 && bp!=-1){
                point=bp ;
            }   
            if(bp==-1){
                point=NULL;
            }
           
          goto options ;
        }
        if(strcmp(choice,"i")==0){
            char inspect [10];
        printf("DEBUG [inspect]: stack, data, object?\n");
        scanf("%s",inspect);
        if(strcmp(inspect,"stack")==0){
        printf("Sp\t--->\t%4d(xxxxxx) xxxxxx\n",sp);
            for(int i=sp-1;i>=0;i--){
                
                if(i==fp){
                    printf("fp\t--->");
                }
                if(i==sp && sp==fp ){
                    printf("sp,fp\t--->");
                }
                if(stack[i].isobjref==true){
                printf("\t\t%04d:   (objref) %p\n",i,(void*)stack[i].u.objref);
                }
                else{
                 printf("\t\t%04d:   (number) %d\n",i,stack[i].u.number);
                }
            }
            goto options;
        }
        else{
            goto options;
        }
        
        
        }



        if(strcmp(choice,"r")==0){
            while (pc!=point)
        {
            instruction_toexecute = anweisungen[pc];
            pc++;
            execute(instruction_toexecute);
           // print_stack();
        }
        goto options ;
            
        }
        if(strcmp(choice,"l")==0){
        while (string_pc < instructions_num)
        {
            instruction_toexecute = anweisungen[string_pc];
          //  printf("before %d \n",string_pc);
            tostring(instruction_toexecute);
            string_pc++;
          //   printf("after %d \n",string_pc);

        }
            string_pc=0;
            goto options;
        }
         
         
         
         } 
         
      

    }
    }
    else if (argc==2){
    if (strstr(argv[1], ".bin") != NULL)
    {
        
        if ((filep = fopen(argv[1], "r")) == NULL)
        {
            perror("ERROR - fopen");
            exit(1);
        }
        fread(&format, sizeof(int), 1, filep); //read njbf
        if (format != 1178749518)
        {
            printf("this is not a ninja binary file \n");
            exit(1);
        }
        fread(&version, sizeof(int), 1, filep);          //read version
        fread(&instructions_num, sizeof(int), 1, filep); //read instructions
        fread(&static_vars, sizeof(int), 1, filep);      //num of global variables
        sda = malloc(static_vars * sizeof(ObjRef));
        int anweisungen[instructions_num];
        while ((fread(&inst, sizeof(int), 1, filep)) == 1)
        {
            anweisungen[inst_counter] = inst;
            inst_counter++;
        }
        fclose(filep);
        for (i = 0; i < sizeof(anweisungen) / sizeof(anweisungen[0]); i++)
        {
            printf("%x ", anweisungen[i]);
        }
        puts("");

        while (string_pc < instructions_num)
        {
            instruction_toexecute = anweisungen[string_pc];
          //  printf("before %d \n",string_pc);
            tostring(instruction_toexecute);
            string_pc++;
          //   printf("after %d \n",string_pc);

        }
            printf("%03d:halt\t\n", string_pc); // print halt


        while (anweisungen[pc] != HALT)
        {
            instruction_toexecute = anweisungen[pc];
            pc++;
          //   printf("%03d : pchier\t\n", pc-1); // print halt
            execute(instruction_toexecute);
           // print_stack();
        }
    }
    }
    


    printf("Ninja Virtual Machine ended\n");

    return 0;
}