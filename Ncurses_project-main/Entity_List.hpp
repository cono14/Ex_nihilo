#ifndef ENTITY_LIST_HPP
#define ENTITY_LIST_HPP
class Entity;

/**
 *	Utilizziamo questa struttura dati per mantenere in relazione tra loro
 *	le entita' presenti in una stanza. Ogni stanza del gioco possiede la
 *	propria lista.
 *
 *	Lo scopo principale della classe e' permettere alla stanza stessa di rilevare
 *	collisioni tra le entita' che la occupano. La gestione delle collisioni e'
 *	delegata poi alle entita' stesse.
 *
 *	La lista e' implementata come lista doppiamente concatenata.
 */
class Entity_List {
public:
	/**
	 *	Rileva le collisioni nella stanza e aggiorna
	 *	tutte le entita' presenti.
	 */
	void update() const;

	Entity* search(int key) const;

	void remove(int key);

	void insert(Entity*);

	int size() const;


	Entity_List();

	~Entity_List();

	int enemies() const;

private:
	void check_collisions() const;

	/**
	 *	Struttura dati ausiliaria che rappresenta
	 *	il singolo nodo della lista.
	 */
	struct Node {
		Entity* entity;
		Node* next; Node* prev;

		explicit Node(Entity* e, Node* n = nullptr, Node* p = nullptr)
		: entity{ e }, next{ n }, prev{ p }
		{}
	};

	Node* list_;

	int enemy_count;

	int sz;
};
#endif