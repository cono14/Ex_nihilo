CC = g++
CFLAGS = -lncurses --std=c++17

all: main.o Artifact.o Blueprint.o Bomb.o Boss_Room.o Button.o Dynamic_Entity.o Enemy.o Entity_List.o Entity.o GestioneSchermo.o Level.o Nurse.o Player.o PrimaSchermata.o Projectile.o Room.o Special_Room.o Turret.o Wasp.o Secret_Room.o Explosion.o Timer.o Game_over.o Big.o boss.o 

	$(CC) $(CFLAGS) main.o Artifact.o Blueprint.o Bomb.o Boss_Room.o Button.o Dynamic_Entity.o Enemy.o Entity_List.o Entity.o GestioneSchermo.o Level.o Nurse.o Player.o PrimaSchermata.o Projectile.o Room.o Special_Room.o Turret.o Wasp.o Secret_Room.o Explosion.o Timer.o Game_over.o Big.o boss.o -o program

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Artifact.o: Artifact.cpp
	$(CC) $(CFLAGS) -c Artifact.cpp

Blueprint.o: Blueprint.cpp
	$(CC) $(CFLAGS) -c Blueprint.cpp

Bomb.o: Bomb.cpp
	$(CC) $(CFLAGS) -c Bomb.cpp

Boss_Room.o: Boss_Room.cpp
	$(CC) $(CFLAGS) -c Boss_Room.cpp

Button.o: Button.cpp
	$(CC) $(CFLAGS) -c Button.cpp

Dynamic_Entity.o: Dynamic_Entity.cpp
	$(CC) $(CFLAGS) -c Dynamic_Entity.cpp

Enemy.o: Enemy.cpp
	$(CC) $(CFLAGS) -c Enemy.cpp

Entity_List.o: Entity_List.cpp
	$(CC) $(CFLAGS) -c Entity_List.cpp

Entity.o: Entity.cpp
	$(CC) $(CFLAGS) -c Entity.cpp

GestioneSchermo.o: GestioneSchermo.cpp
	$(CC) $(CFLAGS) -c GestioneSchermo.cpp

Level.o: Level.cpp
	$(CC) $(CFLAGS) -c Level.cpp

Nurse.o: Nurse.cpp
	$(CC) $(CFLAGS) -c Nurse.cpp

Player.o: Player.cpp
	$(CC) $(CFLAGS) -c Player.cpp

PrimaSchermata.o: PrimaSchermata.cpp
	$(CC) $(CFLAGS) -c PrimaSchermata.cpp

Projectile.o: Projectile.cpp
	$(CC) $(CFLAGS) -c Projectile.cpp

Room.o: Room.cpp
	$(CC) $(CFLAGS) -c Room.cpp

Special_Room.o: Special_Room.cpp
	$(CC) $(CFLAGS) -c Special_Room.cpp

Turret.o: Turret.cpp
	$(CC) $(CFLAGS) -c Turret.cpp

Wasp.o: Wasp.cpp
	$(CC) $(CFLAGS) -c Wasp.cpp

Secret_Room.o: Secret_Room.cpp
	$(CC) $(CFLAGS) -c Secret_Room.cpp

Explosion.o: Explosion.cpp
	$(CC) $(CFLAGS) -c Explosion.cpp

Timer.o: Timer.cpp
	$(CC) $(CFLAGS) -c Timer.cpp

Game_over.o: Game_over.cpp
	$(CC) $(CFLAGS) -c Game_over.cpp

Big.o: Big.cpp
	$(CC) $(CFLAGS) -c Big.cpp

boss.o: boss.cpp
	$(CC) $(CFLAGS) -c boss.cpp

clean:
	rm -f *.o program

