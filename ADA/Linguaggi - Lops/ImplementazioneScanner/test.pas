(* 1*)  PROGRAM TEST;
(* 2*) (* Questo programma è una prova per testare l'analizzatore lessicale *)
(* 3*) VAR
(* 4*)   indice,contatore :integer;
(* 5*)   nome: char;
(* 6*)   test: boolean;
(* 7*)   peso,altezza: real;
(* 8*) BEGIN
         h1=0;
(* 9*)   nome := 'a';
(*10*)   WHILE indice <= 0  DO
(*11*)     BEGIN
(*12*)       peso := 76.12 ;
(*13*)       altezza := 178.;
(*14*)       contatore := contatore + 1;
(*15*)     END;
(*16*)   REPEAT (* 1°ciclo *)
(*17*)     REPEAT (*  2°ciclo *)
(*18*)       REPEAT (* 3°ciclo *)   
(*19*)           contatore := 0;
(*20*)           WHILE ( indice + contatore ) < ( indice - contatore )  DO 
(*21*)             BEGIN 
(*22*)               WHILE contatore < 0 DO
(*23*)                 BEGIN
(*24*)                   IF ( altezza * peso ) < ( altezza - peso ) THEN
(*25*)                     BEGIN    
(*26*)                       altezza := 0;
(*27*)                       peso := 2;
(*28*)                     END;
(*29*)                 END;
(*30*)               nome := 'l''uno';
(*31*)             END;
(*32*)       UNTIL indice = 0; (* fine 3°ciclo *)
(*33*)       nome :=  'K';
(*34*)       peso := 40xyz; 
(*35*)       WHILE   (( indice * contatore )  / peso ) * altezza DO
(*36*)         BEGIN
(*37*)           IF (peso * indice) <= ( altezza - contatore ) THEN
(*38*)             BEGIN
(*39*)               nome := "buono" ;
(*40*)             END;
(*41*)         END;
(*42*)     UNTIL contatore != 0; (* fine 2°ciclo *)  
(*43*)   UNTIL test = 0;  (*fine 1°ciclo *)
(* non funziona qui *)  h2=0;
(*44*) END.
h3=i;
h4=j;
(*fine*)
