      Program Random1d
      Implicit None

Cccccccccccccccccccccccccc
C     Random Walk 1d     C
Cccccccccccccccccccccccccc

      Integer Sstmm,NumberOfJumps,NumberOfCycles,MaxLattice,I,
     &     CurrentPosition,J,K,CycleMultiplication

      Parameter (MaxLattice = 100000)
      Parameter (CycleMultiplication = 1000)

      Double Precision Distribution(-MaxLattice:MaxLattice),Normalization,
     &     P,M1,RandomNumber

Ccccccccccccccccccccccccc
C     Initialize Rng    C
Ccccccccccccccccccccccccc

      M1 = 0.001d0*Dble(Mod((10+10*Sstmm()),1000))

      If(M1.Lt.0.001d0) M1 = 0.001d0
      If(M1.Gt.0.999d0) M1 = 0.999d0

      Call InitializeRandomNumberGenerator(M1)
      Call Sample(1,1)
 
Ccccccccccccccccccccccccccccccc
C     Read Input From Disk    C
Ccccccccccccccccccccccccccccccc

      Write(*,*) 'Number of Cycles (x ',CycleMultiplication,')      ? '
      Read(*,*) NumberOfCycles

      Write(*,*) 'Number of Jumps/Cycle   ? '
      Read(*,*) NumberOfJumps

      Do I=-MaxLattice,MaxLattice
         Distribution(I) = 0.0d0
      Enddo

      Normalization = 0.0d0
      
Ccccccccccccccccccccccccccc
C     Loop Over Cycles    C
Ccccccccccccccccccccccccccc

      Do K=1,NumberOfCycles
      If (mod(K,10).Eq.0) Then
        Write(*,*) 'Cycle: ',K
      Endif

        Do J=1,CycleMultiplication
          
          Call Sample(2,1)
          
          CurrentPosition = 0
         
CCccccccccccccccccccccccccccccccccccc
C     Perform The Random Walk       C
C     Go Up Or Down With Prob.0.5   C
Ccccccccccccccccccccccccccccccccccccc

c     replace 0.5d0 by 0.8d0	

          Do I=1,NumberOfJumps
            If(RandomNumber().Lt.0.5d0) Then
              CurrentPosition = CurrentPosition + 1
            Else
              CurrentPosition = CurrentPosition - 1
            Endif
            
            Call Sample(3,CurrentPosition)
          Enddo

          Normalization = Normalization + 1.0d0

          If(CurrentPosition.Ge.-MaxLattice.Or.CurrentPosition.Le.MaxLattice) 
     &      Distribution(CurrentPosition) = Distribution(CurrentPosition) + 1.0d0
         Enddo
      Enddo

Ccccccccccccccccccccccc
C     Write Results   C
Ccccccccccccccccccccccc

      Call Sample(4,1)

      Open(21,File="results.dat")

      Do I=-MaxLattice,MaxLattice
         If(Distribution(I).Gt.0.5d0) Then
            Distribution(I) = Distribution(I)/Normalization
            P        = 0.5d0*Dlog(2.0d0/
     &           (Dble(NumberOfJumps)*4.0d0*Datan(1.0d0))) - 
     &           ((Dble(I*I))/(2.0d0*Dble(NumberOfJumps)))

            Write(21,'(I10,2e20.10)') I,Distribution(I),
     &           Dexp(P)
         Endif
      Enddo

      Close(21)

      Stop
      End
