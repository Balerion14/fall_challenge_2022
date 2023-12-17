/**
 * @authors :
 * - Sorann753 (Arthus Doriath)
 * - Balerion14
 * - Snowsdy
 * @date december 2022
 */

#include <string>
#include <stdexcept>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include<tuple>
#include <queue>
#include <map>
#include <list>
#include <chrono>

struct Position
{
    int x;
    int y;

    Position(int _x, int _y) : x(std::move(_x)), y(std::move(_y)) {}
    Position() : x(-1), y(-1) {}
};

//Function that return the distance between two positions
int distance(const int x, const int y, const int x2, const int y2)
{
    return std::abs(x - x2) + std::abs(y - y2);
}

bool isNearCenter(const int x, const int y, const int width, const int height) {
    int centerX = width / 2;
    int centerY = height / 2;
    double dist = abs(centerX - x) + abs(centerY - y);

    if (dist < 0.1) {
        return true;
    } else {
        return false;
    }
}

int get_distance_center(const int x, const int y, const int width, const int height)
{
    int centerX = width / 2;
    int centerY = height / 2;
    int dist = std::abs(centerX - x) + std::abs(centerY - y);
    return dist;
}

/**
 * @brief A generic class of dynamic 2d vector
 * @param T the type stored in the Vector2d
 */
template<typename T>
class Vector2d{

public:

    /**
     * @brief convert a Vector2d of a certain type
     * into another type but with the same sizes
     * @param T2 the type stored in the base Vector2d
     * @param base the Vector2d to convert
     */
    template<typename T2>
    Vector2d(const Vector2d<T2>& base)
    : _sizeX(base._sizeX), _sizeY(base._sizeY), _nb_elements(base._nb_elements)
    {
        _data.reserve(_nb_elements);
        for(const auto& i : base){
            _data.push_back(i);
        }
    }

    Vector2d(size_t dim_X, size_t dim_Y)
    : _sizeX(dim_X), _sizeY(dim_Y), _nb_elements(dim_X * dim_Y)
    {
        _data.resize(_nb_elements);
    }

    Vector2d(std::vector<T>&& base, size_t dim_X, size_t dim_Y)
    : _data(std::move(base)), _sizeX(dim_X), _sizeY(dim_Y), _nb_elements(dim_X * dim_Y)
    {}

    //making default the special member functions
    Vector2d() = default;
    Vector2d(const Vector2d&) = default;
    Vector2d(Vector2d&&) = default;
    Vector2d& operator=(const Vector2d&) = default;
    Vector2d& operator=(Vector2d&&) = default;
    ~Vector2d() = default;

    /**
     * @brief operator() to access data
     * @param X the x coordinate in the Vector2d
     * @param Y the y coordinate in the Vector2d
     * @return a reference to the element
     */
    [[nodiscard]] constexpr
    T& operator()(size_t X, size_t Y) noexcept{

        return _data[ Y * _sizeX + X ];
    }

    /**
     * @brief operator() to access data
     * @param X the x coordinate in the Vector2d
     * @param Y the y coordinate in the Vector2d
     * @return a const reference to the element
     */
    [[nodiscard]] constexpr
    const T& operator()(size_t X, size_t Y) const noexcept{

        return _data[ Y * _sizeX + X ];
    }

    /**
     * @brief member function to access data safely
     * @param X the x coordinate in the Vector2d
     * @param Y the y coordinate in the Vector2d
     * @return a const reference to the element
     */
    [[nodiscard]] constexpr
    const T& at(size_t X, size_t Y) const {

        if(X >= _sizeX || Y >= _sizeY){
            throw std::out_of_range(
                std::string("ERROR : trying to access index out of the Vector2d : X-> ")+ std::to_string(X)
                + std::string(" Y-> ") + std::to_string(Y));
        }
        return _data.at(Y * _sizeX + X);
    }

    /**
     * @brief member function to access data safely
     * @param X the x coordinate in the Vector2d
     * @param Y the y coordinate in the Vector2d
     * @return a const reference to the element
     */
    [[nodiscard]] constexpr
    T& at(size_t X, size_t Y) {

        if(X >= _sizeX || Y >= _sizeY){
            throw std::out_of_range(
                std::string("ERROR : trying to access index out of the Vector2d : X-> ")+ std::to_string(X)
                + std::string(" Y-> ") + std::to_string(Y));
        }
        return _data.at(Y * _sizeX + X);
    }



    /**
     * @brief get the size of the whole Vector2d
     * @param none
     * @return the number of elements in the Vector2d
     */
    [[nodiscard]] constexpr
    size_t size() const noexcept {
        return _nb_elements;
    }

    /**
     * @brief get the width of the Vector2d
     * @param none
     * @return the number of elements in a row of the Vector2d
     */
    [[nodiscard]] constexpr
    size_t width() const noexcept {
        return _sizeX;
    }

    /**
     * @brief get the height of the Vector2d
     * @param none
     * @return the number of elements in a column of the Vector2d
     */
    [[nodiscard]] constexpr
    size_t height() const noexcept {
        return _sizeY;
    }
    


    /**
     * @brief get an iterator to the begin of the Vector
     * @param none
     * @return an iterator to the first element
     */
    [[nodiscard]] constexpr
    auto begin() noexcept {
        return _data.begin();
    }

    /**
     * @brief get an iterator to the begin of the Vector
     * @param none
     * @return a const iterator to the first element
     */
    [[nodiscard]] constexpr
    auto begin() const noexcept {
        return _data.begin();
    }

    /**
    * @brief get an iterator to the end of the Vector
    * @param none
    * @return an iterator to the last element
    */
    [[nodiscard]] constexpr
    auto end() noexcept {
        return _data.end();
    }

    /**
    * @brief get an iterator to the end of the Vector
    * @param none
    * @return a const iterator to the last element
    */
    [[nodiscard]] constexpr
    auto end() const noexcept {
        return _data.end();
    }

    /**
    * @brief get a const reference to the data
    * @param none
    * @return const std::vector&
    */
    [[nodiscard]] constexpr
    const std::vector<T>& data() const noexcept {
        return _data;
    }

    /**
    * @brief swap the content of two Vector2d
    * @param other another Vector2d
    * @return none
    */
    constexpr void swap(Vector2d& other) {
        _data.swap(other.data);
    }

    /**
    * @brief check if a coordinate is in the bond of the Vector2d
    * @param X the X coordinate of the data
    * @param Y the Y coordinate of the data
    * @return true if in Vector2d, false else
    */
    constexpr bool is_in_vector(size_t X, size_t Y) const noexcept{
    
        return (Y * _sizeX + X) < _nb_elements && X < _sizeX && Y < _sizeY;
    }

    void resize(size_t X, size_t Y) {
        _sizeX = X;
        _sizeY = Y;
        _nb_elements = X * Y;
        _data.resize(_nb_elements);
    }

protected:

    std::vector<T> _data{}; //a vector storing the data
    size_t _sizeX{};
    size_t _sizeY{};
    size_t _nb_elements{};
};



/** 
 * @brief  pour formaté les commandes à utiliser pour le jeu
 * @example  -Command moveCommand(Command::MOVE, 5, 0, 1, 1, 2);
 *           -Command buildCommand(Command::BUILD, 3, 4);
 *           -Command spawnCommand(Command::SPAWN, 10, 1, 0);
 *           -Command waitCommand(Command::WAIT);
 *           -Command messageCommand(Command::MESSAGE, "Hello World!");
 */
class Command {
    public:
        enum Type {
            MOVE,
            BUILD,
            SPAWN,
            WAIT,
            MESSAGE
        };

        Type type;
        int amount;
        Position origin;
        Position destination;
        Position position;
        std::string message;

        Command(Type _type) : type(std::move(_type)) 
        {
            if(type == Type::WAIT)
            {
                std::cout<<"WAIT;";
            }
            else
            {
                throw std::invalid_argument("Error : Command type not found");
            }
        }

        Command(Type _type, int _amount, int _fromX, int _fromY, int _toX, int _toY, int _x, int _y)// -1 = no value
            : type(std::move(_type)), amount(std::move(_amount)), origin(std::move(_fromX), std::move(_fromY))
            , destination(std::move(_toX), std::move(_toY)), position(std::move(_x), std::move(_y)) 
        {
            if(type == Type::MOVE)
            {
                std::cout << "MOVE" << " " << amount <<" " << origin.x << " " << origin.y << " " << destination.x << " " << destination.y << ";" ;
            }
            else if(type == Type::BUILD)
            {
                std::cout << "BUILD" << " " << position.x << " " << position.y << ";";
            }
            else if(type == Type::SPAWN)
            {
                std::cout << "SPAWN" << " " << amount << " " << position.x << " " << position.y << ";";
            }
            else
            {
                throw std::invalid_argument("Error : Command type not found");
            }
        }

        Command(Type _type, std::string _message) : type(std::move(_type)), message(std::move(_message)) 
        {
            if(type == Type::MESSAGE)
            {
                std::cout << "MESSAGE" << " " << message << ";";
            }
            else
            {
                throw std::invalid_argument("Error : Command type not found");
            }
        }
};

class Game_data
{
    public:
        int my_matter;
        int opp_matter;
        int nb_tour = 0;//voir si c est bien 0 au depart
        //TODO : Rajouter attribut pour les données general du jeu qu on pourrait avoir besoin par la suite de determiner
        //...

        void update()
        {
            nb_tour++;
            std::cin >> my_matter >> opp_matter; std::cin.ignore();
        }

        //TODO : Add fonction pour des operations lie au donnees general du jeu
        //...
};

/**
 * @brief Class that represent the board of the game
 */
class Board {

    private:
        struct Neighboor
        {
            int x;
            int y;
            bool is_exist;
        };
        typedef Neighboor* p_neighbour;
        
        struct Case 
        {
            int scrap_amount;
            int owner; // 1 = me, 0 = foe, -1 = neutral
            int units;
            int recycler;
            int can_build;
            int can_spawn;
            int in_range_of_recycler;
            int x;
            int y;
            std::array<Neighboor, 8> neighbours;// -1 = no neighbour
        };
        typedef Case* p_case;

        int width;//x
        int height;//y
        
        Vector2d<Case> board;
        std::vector<Case> cells_opponent;
        std::vector<Case> my_cells;
        std::vector<Case> neutral_cells;

    public:
        Board() 
        {
            std::cin >> width >> height; std::cin.ignore();
            // std::clog << "width: " << width << " " << "height: " << height << std::endl;
            board.resize(width, height);//Ligne importante pour redimensionner un vector 2D
            //std::clog << "width: " << width << " " << "height: " << height << std::endl;
            std::clog << "----------test case voisine\n";
            for (int x = 0; x < width; x++) 
            {
                for (int y = 0; y < height; y++) 
                {
                    determinate_neighboors(x, y);
                    /*std::clog << "x : " << x << " " << "y : " << y <<" \n";
                    //test affichage
                    for(int i = 0; i < 8; i++)
                    {
                        std::clog << board(x,y).neighbours[i].x << " " << board(x,y).neighbours[i].y
                                  << " " << (board(x,y).neighbours[i].is_exist ? "True" : "False") << std::endl;
                    }*/
                }
            }
            std::clog << "----------\n";
        }

        //Fonction qui permet de determiner les voisins de chaque case (si pas de voisin alors -1)
        // à apeler dans le constructeur juste apres le resize afin de donner à chaque case du plateau de jeu ses voisins
        void determinate_neighboors(int x, int y) noexcept
        {
            char compteurNeighboors = 0;
            // N := {-1, 0, 1}
            for(int i = -1; i <= 1; i++){ // i ∈ N
                for(int j = -1; j <= 1; j++){ // j ∈ N
                    // {i, j} ∈ N²
                    if(i == 0 && j == 0){
                        continue;
                    }
                    // {i, j} ∈ N² \ {0, 0}
                    // n(N) = 3
                    // n({i, j}) = n(N)² - 1
                    //           = 9 - 1 = 8

                    // board.is_in_vector(x+i, y+j) ∈ {true, false}
                    if(board.is_in_vector(x+i, y+j)){
                        // board(x+i, y+j) ∈ {board} / {board(x, y)}
                        board(x, y).neighbours[compteurNeighboors].x = x+i;
                        board(x, y).neighbours[compteurNeighboors].y = y+j;
                        board(x, y).neighbours[compteurNeighboors].is_exist = true;
                    }
                    else{
                        // board(x+i, y+j) ∈ {∅}
                        board(x, y).neighbours[compteurNeighboors].x = -1;
                        board(x, y).neighbours[compteurNeighboors].y = -1;
                        board(x, y).neighbours[compteurNeighboors].is_exist = false;
                    }
                    
                    compteurNeighboors++;
                    // compteurNeighboors_l+1 = compteurNeighboors_l + 1
                    // l ∈ [1, n({i, j})] -> l ∈ [1, 8]
                    // compteurNeighboors ∈ [0, 7]
                }
            }
        }

        void update_cells_opponent()
        {
            cells_opponent.clear();
            for (const Case& i : board) {
                if (i.owner == 0) {
                    cells_opponent.push_back(i);
                }
            }
        }

        void update_my_cells()
        {
            my_cells.clear();
            for (const Case& i : board) {
                if (i.owner == 1) {
                    my_cells.push_back(i);
                }
            }
        }

        void update_neutral_cells()
        {
            neutral_cells.clear();
            for (const Case& i : board) {
                if (i.owner == -1 && i.scrap_amount > 0) {
                    neutral_cells.push_back(i);
                }
            }
        }

        void update()
        {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    // TODO : don't use temporary variables to store them into the class.
                    int scrap_amount;
                    int owner; // 1 = me, 0 = foe, -1 = neutral
                    int units;
                    int recycler;
                    int can_build;
                    int can_spawn;
                    int in_range_of_recycler;
                    std::cin >> scrap_amount >> owner >> units >> recycler >> can_build >> can_spawn >> in_range_of_recycler; std::cin.ignore();
                    board(j, i).scrap_amount = scrap_amount;
                    board(j, i).owner = owner;
                    board(j, i).units = units;
                    board(j, i).recycler = recycler;
                    board(j, i).can_build = can_build;
                    board(j, i).can_spawn = can_spawn;
                    board(j, i).in_range_of_recycler = in_range_of_recycler;
                    board(j, i).x = j;
                    board(j, i).y = i;
                }
            }

            update_cells_opponent();
            update_my_cells();
            update_neutral_cells();
            //affichage cells_opponent
            /*std::clog << "---------- cells opposent\n";
            for(int i = 0; i < cells_opponent.size(); i++)
            {
                std::clog << "cells_opponent[" << i << "].x: " << cells_opponent[i].x << " " << "cells_opponent[" << i << "].y: " << cells_opponent[i].y << std::endl;
            }
            //affichage my_cells
            std::clog << "---------- my_cells\n";
            for(int i = 0; i < my_cells.size(); i++)
            {
                std::clog << "my_cells[" << i << "].x: " << my_cells[i].x << " " << "my_cells[" << i << "].y: " << my_cells[i].y << std::endl;
            }
            //affichage neutral_cells
            std::clog << "---------- neutral_cells\n";
            for(int i = 0; i < neutral_cells.size(); i++)
            {
                std::clog << "neutral_cells[" << i << "].x: " << neutral_cells[i].x << " " << "neutral_cells[" << i << "].y: " << neutral_cells[i].y << std::endl;
            }*/
        }

        //TODO : Add fonction pour des operations lie au plateau de jeu
        //...

        //Fonction qui retourne un tableau 2d de type vector<vector<Case>>
        Vector2d<Case>& get_board()  noexcept{
            return board;
        }

        const Vector2d<Case>& get_board() const noexcept{
            return board;
        }

        int get_width() const noexcept {
            return width;
        }

        int get_height() const noexcept {
            return height;
        }

        std::vector<Case>& get_cell_opponent() noexcept {
            return cells_opponent;
        }

        std::vector<Case>& get_my_cells() noexcept {
            return my_cells;
        }

        std::vector<Case>& get_neutral_cells() noexcept {
            return neutral_cells;
        }
};

//bool within_fear_recycler_around(const int x, const int y);

class Graphe
{
    typedef struct Noeud_graphe
    {
        float cout_g, cout_h, cout_f;
        std::pair<int,int> parent;
        int distance_center;
    }Noeud;

    private:
        typedef std::map<std::pair<int,int>,Noeud> type;
        type file_open;
        type file_close;
        const Board* p_board = nullptr;
        std::list<Position> chemin;
        std::vector<Position> array_remove;
        int from_x;
        int from_y;
        int to_x;
        int to_y;
        int nb_unite;

    public:
        Graphe(const Board* _board) : p_board(_board){
            if(p_board == nullptr)
            {
                throw std::invalid_argument("board is null");
            }
        } 

        void init_research_court_chemin(int _from_x, int _from_y, int _to_x, int _to_y, int nb_units, std::vector<Position> &_array_remove)
        {
            from_x = _from_x;
            from_y = _from_y;
            to_x = _to_x;
            to_y = _to_y;
            nb_unite = nb_units;
            array_remove = _array_remove;
        }

        bool within_fear_recycler_around(const int x, const int y)
        {
            const Board& board = *p_board;
            for(int i = 0; i < 8; i++)
            {
                if(i == 1 || i == 3 || i == 4 || i == 6)
                {
                    int x_ = board.get_board()(x,y).neighbours[i].x;
                    int y_ = board.get_board()(x,y).neighbours[i].y;
                    if(x_ != -1 && y_ != -1){
                        if(board.get_board()(x_,y_).recycler == 1){return true;}
                    }
  
                }
            }
            return false;
        }

        bool verif_array_remove(const int x, const int y)
        {
            for(int i = 0; i < array_remove.size();i++)
            {
                if(x == array_remove[i].x && y == array_remove[i].y){return true;}
            }
            return false;
        }

        bool deja_present_dans_liste(std::pair<int,int> n, type& l){
            type::iterator i = l.find(n);
            if (i==l.end())
                return false;
            else
                return true;
        }

        void ajouter_cases_adjacentes(std::pair <int,int>& n)
        {
            Noeud tmp;
            const Board& board = *p_board;
            for(int k = 0; k < 8; k++)
            {
                if(k == 1 || k == 3 || k == 4 || k == 6)
                {
                    if(!board.get_board()(n.first,n.second).neighbours[k].is_exist){
                        continue;
                    }

                    int x_voisin = board.get_board()(n.first,n.second).neighbours[k].x;
                    int y_voisin = board.get_board()(n.first,n.second).neighbours[k].y;

                    if(verif_array_remove(x_voisin, y_voisin))
                        {continue;}

                    if(board.get_board()(x_voisin,y_voisin).scrap_amount == 1 && !within_fear_recycler_around(x_voisin,y_voisin) && board.get_board()(x_voisin,y_voisin).recycler != 1 || board.get_board()(x_voisin,y_voisin).scrap_amount > 1 && board.get_board()(x_voisin,y_voisin).recycler != 1)
                    {
                        if(board.get_board()(x_voisin,y_voisin).owner == -1 || board.get_board()(x_voisin,y_voisin).owner == 1 || board.get_board()(x_voisin,y_voisin).owner == 0)// && board.get_board()(x_voisin,y_voisin).units <= nb_unite)
                        {   
                            std::pair<int,int> it(x_voisin,y_voisin);
                            
                            if (!deja_present_dans_liste(it, file_close))
                            {
                                tmp.cout_g = file_close[n].cout_g + distance(x_voisin,y_voisin,n.first,n.second);
                                tmp.cout_h = distance(x_voisin,y_voisin,to_x,to_y);
                                tmp.cout_f = tmp.cout_g + tmp.cout_h;
                                tmp.parent = n;
                                tmp.distance_center = get_distance_center(x_voisin,y_voisin,board.get_width(),board.get_height());

                                if (deja_present_dans_liste(it, file_open))
                                {
                                    /* le noeud est deja present dans la liste ouverte, il faut comparer les couts */
                                    if (tmp.cout_f < file_open[it].cout_f){// || (tmp.cout_f == file_open[it].cout_f && tmp.distance_center < file_open[it].distance_center)){//isNearCenter(x_voisin, y_voisin, board.get_width(), board.get_height())
                                        /* si le nouveau chemin est meilleur, on update */
                                        file_open[it]=tmp;
                                    }
                                    /* le noeud courant a un moins bon chemin, on ne change rien */
                                }
                                else
                                {
                                    /* le noeud n'est pas present dans la liste ouverte, on l'ajoute */
                                    file_open[std::pair<int,int>(x_voisin,y_voisin)]=tmp;
                         
                               }
                            }
                        }
                    }
                }
            }
        }

        std::pair<int,int> meilleur_noeud(type& l)
        {
            float m_coutf = l.begin()->second.cout_f;
            int distance = l.begin()->second.distance_center;
            std::pair<int,int> m_noeud = l.begin()->first;

            for (type::iterator i = l.begin(); i!=l.end(); i++)
            {
                if (i->second.cout_f < m_coutf){// || (i->second.cout_f == m_coutf && i->second.distance_center < distance)){
                    m_coutf = i->second.cout_f;
                    m_noeud = i->first;
                }
            }
            return m_noeud;
        }

        void ajouter_liste_fermee(std::pair<int,int>& p)
        {
            Noeud& n = file_open[p];
            file_close[p]=n;

            // il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable
            if (file_open.erase(p)==0)
                std::cerr << "n'apparait pas dans la liste ouverte, impossible   supprimer" << std::endl;
            return;
        }

        void retrouver_chemin()
        {
            // l'arrivee est le dernier element de la liste fermee.
            Noeud& tmp = file_close[std::pair<int, int>(to_x,to_y)];

            Position n;
            std::pair<int,int> prec;
            n.x = to_x;
            n.y = to_y;
            prec.first  = tmp.parent.first;
            prec.second = tmp.parent.second;
            chemin.push_front(n);

            while (prec != std::pair<int,int>(from_x,from_y)){
                n.x = prec.first;
                n.y = prec.second;
                chemin.push_front(n);

                tmp = file_close[tmp.parent];
                prec.first  = tmp.parent.first;
                prec.second = tmp.parent.second;
            }
        }

        void loop_search_chemin()
        {
            Noeud depart;
            depart.parent.first  = from_x;
            depart.parent.second = from_y;

            std::pair <int,int> courant;

            /* deroulement de l'algo A* */

            courant.first  = from_x;
            courant.second = from_y;
            // ajout de courant dans la liste ouverte

            file_open[courant]=depart;
            ajouter_liste_fermee(courant);
            ajouter_cases_adjacentes(courant);


            while( !((courant.first == to_x) && (courant.second == to_y))
                    &&
                (!file_open.empty())
                ){

                // on cherche le meilleur noeud de la liste ouverte, on sait qu'elle n'est pas vide donc il existe
                courant = meilleur_noeud(file_open);

                // on le passe dans la liste fermee, il ne peut pas deja y etre
                ajouter_liste_fermee(courant);

                ajouter_cases_adjacentes(courant);
            }

            if ((courant.first == to_x) && (courant.second == to_y)){
                retrouver_chemin();
            }else{
                    /* pas de solution */
            }
        }

        void clear_list()
        {
            file_open.clear();
            file_close.clear();
            chemin.clear();
            array_remove.clear();
        }

        std::list<Position>& get_list_chemin() noexcept {
            return chemin;
        }
        
};

struct Entity
{
    int x;
    int y;
    //TODO : Eventuellement rajouter des attributs pour les entités
    //...
};
typedef Entity* p_entity;

/**
 * @brief class that represent a different entities of the game (recycler, unit, ...)
 */
class Entities {

    private:
        std::vector<Entity> opponent_recycler;
        std::vector<Entity> opponent_unit;
        std::vector<Entity> my_recycler;
        std::vector<Entity> my_unit;
        //TODO : Rajout d'eventuels autre attributs pour les entites
        //...

    public:
        Entities(Board const& board)
        {
            std::cerr<<"Initialisation des entités"<<std::endl;
            update_opponent_recycler(board);
            //Affichage des coordonnées des recyclers ennemis
            /*for(int i = 0; i < opponent_recycler.size(); i++)
            {
                std::cerr << "Recycler ennemi : " << opponent_recycler[i].x << " " << opponent_recycler[i].y << std::endl;
            }*/
            update_opponent_unit(board);
            //Affichage des coordonnées des unités ennemies
            /*for(int i = 0; i < opponent_unit.size(); i++)
            {
                std::cerr << "Unité ennemie : " << opponent_unit[i].x << " " << opponent_unit[i].y << std::endl;
            }*/
            update_my_recycler(board);
            //Affichage des coordonnées des recyclers alliés
            /*for(int i = 0; i < my_recycler.size(); i++)
            {
                std::cerr << "Recycler allié : " << my_recycler[i].x << " " << my_recycler[i].y << std::endl;
            }*/
            update_my_unit(board);
            //Affichage des coordonnées des unités alliées
            /*for(int i = 0; i < my_unit.size(); i++)
            {
                std::cerr << "Unité alliée : " << my_unit[i].x << " " << my_unit[i].y << std::endl;
            }*/
            std::cerr<<"Fin de l'initialisation des entités"<<std::endl;
        }

        //Function that update the array opponent_recycler depuis le tableau board passé en paramètre
        void update_opponent_recycler(Board const & board)
        {
            for(int i = 0; i < board.get_width(); i++)
            {
                for(int j = 0; j < board.get_height(); j++)
                {
                    if(board.get_board()(i, j).owner == 0 && board.get_board()(i, j).recycler == 1)
                    {
                        Entity entity;
                        entity.x = i;
                        entity.y = j;
                        opponent_recycler.push_back(entity);
                    }
                }
            }
        }

        //Function that update the array opponent_unit depuis le tableau board passé en paramètre
        void update_opponent_unit(Board const& board)
        {
            for(int i = 0; i < board.get_width(); i++)
            {
                for(int j = 0; j < board.get_height(); j++)
                {
                    if(board.get_board()(i, j).owner == 0 && board.get_board()(i, j).units > 0)
                    {
                        for(int k = 0; k < board.get_board()(i, j).units; k++)
                        {
                            Entity entity;
                            entity.x = i;
                            entity.y = j;
                            opponent_unit.push_back(entity);
                        }
                    }
                }
            }
        }

        //Function that update the array my_recycler depuis le tableau board passé en paramètre
        void update_my_recycler(Board const& board)
        {
            for(int i = 0; i < board.get_width(); i++)
            {
                for(int j = 0; j < board.get_height(); j++)
                {
                    if(board.get_board()(i, j).owner == 1 && board.get_board()(i, j).recycler == 1)
                    {
                        Entity entity;
                        entity.x = i;
                        entity.y = j;
                        my_recycler.push_back(entity);
                    }
                }
            }
        }

        //Function that update the array my_unit depuis le tableau board passé en paramètre
        void update_my_unit(Board const& board)
        {
            for(int i = 0; i < board.get_width(); i++)
            {
                for(int j = 0; j < board.get_height(); j++)
                {
                    if(board.get_board()(i, j).owner == 1 && board.get_board()(i, j).units > 0)
                    {
                        for(int k = 0; k < board.get_board()(i, j).units; k++)
                        {
                            Entity entity;
                            entity.x = i;
                            entity.y = j;
                            my_unit.push_back(entity);
                        }
                    }
                }
            }
        }

        //TODO : Add fonction pour des operations lie aux entites
        //...

        std::vector<Entity>& get_opponent_recycler() noexcept {
            return opponent_recycler;
        }

        std::vector<Entity>& get_opponent_unit() noexcept {
            return opponent_unit;
        }

        std::vector<Entity>& get_my_recycler() noexcept {
            return my_recycler;
        }

        std::vector<Entity>& get_my_unit() noexcept {
            return my_unit;
        }
};



class IA
{
    private:
        Board& board;
        Entities entities;
        Game_data data;
        Graphe graphe;

    public:
        bool global_fin_early = false;
        int old_ressources = -10;
        IA(Board & _board) : board(_board), entities(_board), graphe(&board){}

        // Procedure : boucle principale de l'IA 
            /*- update des Data
            - sauvegare des donnée qui permettra au methode de cette classe d avoir les données les plus recente en temps reel quand elle fera appel a action()
            - update du Board
            - pas besoin de sauvegarde car c est appelé dans le main et passer dans une liste d'initialisation
            - update des Entities
            - idem
            - appel de la fonction action() pour faire les actions sur un tour*/
        //
        void loop_game()
        {   
            data.update(); // copie pour avoir acces aux donnees general du jeu plus facilement pour l'IA dans les differentes methodes apres les initialisations
            board.update();
            entities = Entities(board);
            graphe = Graphe(&board);
            action();
            //print_value_board();
        }

        //Fonction qui permet d'effectuer les actions recommandées par l'IA
        void action()
        {
            //exemple avec wait et print message
            /*Command waitCommand(Command::WAIT);
            Command messageCommand(Command::MESSAGE, "Hello World!");
            Command move(Command::MOVE, 1, 12, 4, 12, 5, -1, -1);

            std::cout << "WAIT" << std::endl;*/
            basic_strat();
        }

        //test affichage value...
        //ATTENTION : 
        void print_value_board()
        {
            for (int i = 0; i < board.get_width(); i++) {
                for (int j = 0; j < board.get_height(); j++) {
                    std::clog <<i<<" "<<j<<" "<<"/"<<board.get_board()(i, j).owner<<"\n";
                }
            }
            std::clog<<"-----\n";
        }

        bool verif_adjacency(const int x, const int y, const int x_origine, const int y_origine)
        {
            for(int i = 0; i < 8; i++)
            {
                if(i == 1 || i == 3 || i == 4 || i == 6)//pas les diagonnales
                {
                    if(board.get_board()(x_origine,y_origine).neighbours[i].x == x && board.get_board()(x_origine,y_origine).neighbours[i].y == y){return true;}
                }
            }
            return false;
        }

        bool verif_if_cell_empty_adjecency(const int x, const int y)
        {
            for(int i = 0; i < 8; i++)
            {
                if(board.get_board()(x, y).neighbours[i].is_exist == false)
                {
                    return true;
                }
            }
            return false;
        }

        void calcule_min_distance_entre_my_unit_cellBoard_empty(std::vector<Position> & array_remove_value_unit_allie,std::vector<Position> const & array_remove_value,std::tuple<int, int, int> & best_position){
            int _distance_opp_unit = -1;
            int min = 1000;
            int max_x_move = -1;
            int max_y_move = -1;

            std::vector<Position> copy_neutral_cells;
            for(int i = 0; i < board.get_neutral_cells().size(); i++){
                Position pos;
                pos.x = board.get_neutral_cells()[i].x;
                pos.y = board.get_neutral_cells()[i].y;
                copy_neutral_cells.push_back(pos);}
            
            //Cherche dans les deux tableaux si les coordonnees du tableau passe en parametre sont present et supp si c est cas...
            for(int i = 0; i < array_remove_value.size(); i++){
                for(int j = 0; j < copy_neutral_cells.size(); j++){
                    if(copy_neutral_cells[j].x == array_remove_value[i].x && copy_neutral_cells[j].y == array_remove_value[i].y){
                        auto it = copy_neutral_cells.begin();
                        std::advance(it, j);
                        copy_neutral_cells.erase(it);
                        break;}}
            }

            for(int u = 0; u < copy_neutral_cells.size(); u++){  
                for(int i = 0; i <entities.get_my_unit().size();i++){ 
                    if(verif_array_remove(entities.get_my_unit()[i].x,entities.get_my_unit()[i].y,array_remove_value_unit_allie))
                            {continue;}
                    _distance_opp_unit = distance(entities.get_my_unit()[i].x, entities.get_my_unit()[i].y, copy_neutral_cells[u].x, copy_neutral_cells[u].y);
                
                    //std::cerr<<"2dist : "<<_distance_opp_unit<<"\n";
                    if(_distance_opp_unit < min)
                    {
                        min = _distance_opp_unit;
                        max_x_move = copy_neutral_cells[u].x;
                        max_y_move = copy_neutral_cells[u].y;}}
            }
            //std::cerr<<"finrrrr"<<max_x_move<<"/"<<max_y_move<<"\n";
            std::get<0>(best_position) = max_x_move;
            std::get<1>(best_position) = max_y_move;
            std::get<2>(best_position) = min;
        }

        //Add fonction pour des operations lie a l'IA afin de determiner les actions a effectuer
        //TODO...
        void calcule_min_distance_entre_my_unit_cellBoard(std::vector<Position> & array_remove_value_unit_allie,std::vector<Position> const & array_remove_value,std::tuple<int, int, int> & best_position)
        {
            int _distance_opp_unit = -1;
            int min = 1000;
            int max_x_move = -1;
            int max_y_move = -1;

            //copie tableaux pour faire des modifs sans influencer le reste du code
            std::vector<Position> copy_get_opponent_unit;//attention distance par rapport au case annemie et pas juste au unite ennemie(fleme changer nom)
            for(int i = 0; i < board.get_cell_opponent().size(); i++){
                if(board.get_cell_opponent()[i].recycler != 1 && board.get_cell_opponent()[i].units == 0){
                    Position pos;
                    pos.x = board.get_cell_opponent()[i].x;
                    pos.y = board.get_cell_opponent()[i].y;
                    copy_get_opponent_unit.push_back(pos);}}

            std::vector<Position> copy_neutral_cells;
            for(int i = 0; i < board.get_neutral_cells().size(); i++){
                Position pos;
                pos.x = board.get_neutral_cells()[i].x;
                pos.y = board.get_neutral_cells()[i].y;
                copy_neutral_cells.push_back(pos);}

            //Cherche dans les deux tableaux si les coordonnees du tableau passe en parametre sont present et supp si c est cas...
            for(int i = 0; i < array_remove_value.size(); i++){
                bool verif = false;
                for(int j = 0; j < copy_get_opponent_unit.size(); j++){
                    if(copy_get_opponent_unit[j].x == array_remove_value[i].x && copy_get_opponent_unit[j].y == array_remove_value[i].y){
                        auto it = copy_get_opponent_unit.begin();
                        std::advance(it, j);
                        copy_get_opponent_unit.erase(it);
                        verif = true;
                        break;}}
                if(!verif){
                    for(int j = 0; j < copy_neutral_cells.size(); j++){
                        if(copy_neutral_cells[j].x == array_remove_value[i].x && copy_neutral_cells[j].y == array_remove_value[i].y){
                            auto it = copy_neutral_cells.begin();
                            std::advance(it, j);
                            copy_neutral_cells.erase(it);
                            verif = true;
                            break;}}}
            }

            for(int j = 0; j < copy_get_opponent_unit.size(); j++){
                for(int i = 0; i <entities.get_my_unit().size();i++){
                    if(verif_array_remove(entities.get_my_unit()[i].x,entities.get_my_unit()[i].y,array_remove_value_unit_allie))
                            {continue;}
                    _distance_opp_unit = distance(entities.get_my_unit()[i].x, entities.get_my_unit()[i].y, copy_get_opponent_unit[j].x, copy_get_opponent_unit[j].y);

                    //std::cerr<<"dist : "<<_distance_opp_unit<<"\n";
                    if(_distance_opp_unit < min){
                        min = _distance_opp_unit;
                        max_x_move = copy_get_opponent_unit[j].x;
                        max_y_move = copy_get_opponent_unit[j].y;}}  
            }
            
            /*for(int u = 0; u < copy_neutral_cells.size(); u++){  
                for(int i = 0; i <entities.get_my_unit().size();i++){ 
                    if(verif_array_remove(entities.get_my_unit()[i].x,entities.get_my_unit()[i].y,array_remove_value_unit_allie))
                            {continue;}
                    _distance_opp_unit = distance(entities.get_my_unit()[i].x, entities.get_my_unit()[i].y, copy_neutral_cells[u].x, copy_neutral_cells[u].y);
                
                    //std::cerr<<"2dist : "<<_distance_opp_unit<<"\n";
                    if(_distance_opp_unit < min)
                    {
                        min = _distance_opp_unit;
                        max_x_move = copy_neutral_cells[u].x;
                        max_y_move = copy_neutral_cells[u].y;}}
            }*/
            //std::cerr<<"finrrrr"<<max_x_move<<"/"<<max_y_move<<"\n";
            std::get<0>(best_position) = max_x_move;
            std::get<1>(best_position) = max_y_move;
            std::get<2>(best_position) = min;
        }

        void get_information_cell(bool version_case_adjacente, const int x, const int y, std::tuple<int, int, int,int> & information, std::vector<std::tuple<int, int, int,int>> & information_adj)
        {
            if(version_case_adjacente == true){
                for(int k = 0; k < 8; k++){
                    if(k == 1 || k == 3 || k == 4 || k == 6){
                        int voisin_x = board.get_board()(x,y).neighbours[k].x;
                        int voisin_y = board.get_board()(x,y).neighbours[k].y;
                        if(board.get_board()(x,y).neighbours[k].x != -1 && board.get_board()(x,y).neighbours[k].y != -1){
                            information_adj.push_back(std::make_tuple(board.get_board()(voisin_x,voisin_y).owner, board.get_board()(voisin_x,voisin_y).recycler, board.get_board()(voisin_x,voisin_y).units, board.get_board()(voisin_x,voisin_y).scrap_amount));
                        }}}}
                            
            else{
                //parcourir tout les board et recuperer les infos (owner, recycler, nb unit)
                //std::cerr<<"x : "<<x<<" y : "<<y<<"\n";
                bool find = false;
                for(int i = 0; i < board.get_width(); i++){
                    for(int j = 0; j < board.get_height(); j++){
                        if(board.get_board()(i,j).x == x && board.get_board()(i,j).y == y){
                            std::get<0>(information) = board.get_board()(i,j).owner;
                            std::get<1>(information) = board.get_board()(i,j).recycler;
                            std::get<2>(information) = board.get_board()(i,j).units;
                            std::get<3>(information) = board.get_board()(i,j).scrap_amount;
                            find = true;
                            //std::cerr<<"owner : "<<std::get<0>(information)<<" recycler : "<<std::get<1>(information)<<" units : "<<std::get<2>(information)<<"\n";
                            break;}}
                    if(find == true){
                        break;}}}
        }

        void remplir_array_position_en_or_all_dangereux(bool choice, std::vector<Position> &position_to_dodge){
            if(choice == false){//pour allie (eviter case ennemie dangereuse)
                auto plateau = board.get_cell_opponent();
                for(int i = 0; i < board.get_cell_opponent().size();i++){
                    if(plateau[i].recycler == 1 ){//|| plateau[i].units > 0){//voir pour modif si pb
                        Position pos;
                        pos.x = plateau[i].x;
                        pos.y = plateau[i].y;
                        position_to_dodge.push_back(pos);}}
            }
            else{//pour ennemie(eviter case allie dangereuse)
                auto plateau_ennemie = board.get_my_cells();
                for(int i = 0; i < plateau_ennemie.size();i++){
                    if(plateau_ennemie[i].recycler == 1 ){//|| plateau_ennemie[i].units > 0){//voir pour modif si besoin
                        Position pos;
                        pos.x = plateau_ennemie[i].x;
                        pos.y = plateau_ennemie[i].y;
                        position_to_dodge.push_back(pos);}}
            }
        }

        bool within_cell_opp_around(const int x, const int y)
        {
            for(int i = 0; i < 8; i++)
            { 
                int x_ = board.get_board()(x,y).neighbours[i].x;
                int y_ = board.get_board()(x,y).neighbours[i].y;
                if(x_ != -1 && y_ != -1){
                    if(board.get_board()(x_,y_).owner == 0 && board.get_board()(x_,y_).recycler != 1 || board.get_board()(x_,y_).owner == -1 && board.get_board()(x_,y_).scrap_amount > 0){return true;}
                }
            }
            return false;
        }

        bool within_cell_opp_around_version2(const int x, const int y)
        {
            for(int i = 0; i < 8; i++)
            { 
                int x_ = board.get_board()(x,y).neighbours[i].x;
                int y_ = board.get_board()(x,y).neighbours[i].y;
                if(x_ != -1 && y_ != -1){
                    if(board.get_board()(x_,y_).owner == 0 && board.get_board()(x_,y_).recycler != 1){return true;}
                }
            }
            return false;
        }

        bool verif_pos_is_in_arraySaveDist_ennemie(const int x,const int y,const int x_inside,const int y_inside,std::vector<std::vector<std::tuple<int,int,int>>> &save_dist_ennemie,int &dist,int &_index){
            int index = 0;
            bool found = false;
            bool final = false;
            for(int i = 0; i < save_dist_ennemie.size();i++){
                if(x == std::get<0>(save_dist_ennemie[i][0]) && y == std::get<1>(save_dist_ennemie[i][0])){index = i;found = true;_index = index;break;}
            }    
            if(found == true){
                for(int j = 0; j < save_dist_ennemie[index].size();j++){
                    if(x_inside == std::get<0>(save_dist_ennemie[index][j]) && y_inside == std::get<1>(save_dist_ennemie[index][j])){dist = std::get<2>(save_dist_ennemie[index][j]);final = true;break;}
                }
            }
                    
            if(found == true && final == true){
                return true;
            }
            else{return false;}
        }

        void evaluation_ennemie_unit(std::vector<Position> &position_to_dodge,std::vector<Position> const & array_remove_value, std::tuple<int, int, int,int> & best_position,std::vector<std::vector<std::tuple<int,int,int>>> &save_dist_ennemie)
        {
            int _distance_opp_unit = -1;
            int min = 1000;
            int max = -1111;
            int max_x_move = -1;
            int max_y_move = -1;
            int distance_reel = -1;
            int nb_ennemie_adj_tot = -1;
            float score_max = 0;
            float score_min = 100000.0;
            bool not_fear = false;

            //copie tableaux pour faire des modifs sans influencer le reste du code
            std::vector<std::tuple<int,int,int>> copy_get_opponent_unit;//attention distance par rapport au case annemie et pas juste au unite ennemie(fleme changer nom)
            size_t nb_cell_opp = board.get_cell_opponent().size();
            for(int i = 0; i < nb_cell_opp; i++){
                auto cell = board.get_cell_opponent()[i];
                if(cell.recycler != 1 && cell.units > 0){
                    copy_get_opponent_unit.push_back(std::make_tuple(cell.x, cell.y, cell.units));
                    std::vector<std::tuple<int,int,int>> temp;
                    temp.push_back(std::make_tuple(cell.x, cell.y, 0));
                    save_dist_ennemie.push_back(temp);
                }
            }

            size_t array_remove_value_size = array_remove_value.size();
            for(int i = 0; i < array_remove_value_size; i++){
                size_t copy_get_opponent_unit_size = copy_get_opponent_unit.size();
                for(int j = 0; j < copy_get_opponent_unit_size; j++){
                    if(std::get<0>(copy_get_opponent_unit[j]) == array_remove_value[i].x && std::get<1>(copy_get_opponent_unit[j]) == array_remove_value[i].y){
                        auto it = copy_get_opponent_unit.begin();
                        std::advance(it, j);
                        copy_get_opponent_unit.erase(it);
                        break;}}}
            
            //determiner l element le plus dangereux(score le moins eleve(-1))
            remplir_array_position_en_or_all_dangereux(true, position_to_dodge);
            size_t copy_get_opponent_unit_size = copy_get_opponent_unit.size();
            for(int j = 0; j < copy_get_opponent_unit_size; j++)
            {
                not_fear = false;
                score_max = 0;
                min = 1000;
                max = -1111;
                size_t nb_my_cells = board.get_my_cells().size();
                for(int i = 0; i < nb_my_cells; i++){

                    if(board.get_my_cells()[i].recycler != 1 && within_cell_opp_around(board.get_my_cells()[i].x, board.get_my_cells()[i].y)){
                        int dist = -1;
                        int index = -1;
                        if(verif_pos_is_in_arraySaveDist_ennemie(std::get<0>(copy_get_opponent_unit[j]), std::get<1>(copy_get_opponent_unit[j]),board.get_my_cells()[i].x, board.get_my_cells()[i].y,save_dist_ennemie,dist,index)){
                            _distance_opp_unit = dist;
                        }
                        else{
                            //distance
                            graphe.init_research_court_chemin(std::get<0>(copy_get_opponent_unit[j]), std::get<1>(copy_get_opponent_unit[j]),board.get_my_cells()[i].x, board.get_my_cells()[i].y,std::get<2>(copy_get_opponent_unit[j]),position_to_dodge);
                            graphe.loop_search_chemin();
                            _distance_opp_unit = graphe.get_list_chemin().size();
                            /*std::cerr<<"--------chemin1---\n";
                            for(std::list<Position>::iterator it = graphe.get_list_chemin().begin(); it != graphe.get_list_chemin().end(); it++){
                                std::cerr<<"x et y : " << it->x <<"/" << it->y << std::endl;
                            }
                            std::cerr<<"--------chemin1---\n";*/
                            graphe.clear_list();
                            //std::cerr<<"index : "<<index<<std::endl;
                            save_dist_ennemie[index].push_back(std::make_tuple(board.get_my_cells()[i].x, board.get_my_cells()[i].y,_distance_opp_unit));
                        }

                        //std::cerr<<"depart : : "<<std::get<0>(copy_get_opponent_unit[j])<<"/"<<std::get<1>(copy_get_opponent_unit[j])<<"\n";
                        //std::cerr<<"arrive : : "<<board.get_my_cells()[i].x<<"/"<<board.get_my_cells()[i].y<<"\n";
                        //std::cerr<<"dist : "<<_distance_opp_unit<<"\n";
                        //_distance_opp_unit = distance(std::get<0>(copy_get_opponent_unit[j]), std::get<1>(copy_get_opponent_unit[j]),board.get_my_cells()[i].x, board.get_my_cells()[i].y);
                        if(_distance_opp_unit != 0){
                            if(_distance_opp_unit < min){
                                min = _distance_opp_unit;
                            }
                        }
                        
                        if(_distance_opp_unit > max){
                            max = _distance_opp_unit;
                        }
                        
                        if(nb_my_cells - 1 == i && max == 0){not_fear = true;}
                        //std::cerr<<"ee :"<<not_fear<<std::endl;
                    }      
                }
                if(not_fear == false){

                    //Nb unit on the case
                    score_max = min;
                    float nb_unit_one_case = std::get<2>(copy_get_opponent_unit[j]);
                    score_max -= (nb_unit_one_case/2);//coef 1
                    //nb_unit_autour de toi
                    int nb_unit_adj = nb_unit_one_case;
                    std::tuple<int, int, int,int> information;
                    std::vector<std::tuple<int, int, int,int>> information_adj;
                    get_information_cell(true,std::get<0>(copy_get_opponent_unit[j]),std::get<1>(copy_get_opponent_unit[j]),information,information_adj);
                    for(int k = 0; k < information_adj.size();k++){
                        if(std::get<0>(information_adj[k]) == 0){
                            nb_unit_adj += std::get<2>(information_adj[k]);
                            float nb_unit = std::get<2>(information_adj[k]);
                            score_max-= (nb_unit/4);//coef 2
                        }
                    }
                    //std::cerr<<"-----------------------score :"<<score_max<<std::endl;
                    if(score_max < score_min){
                        score_min = score_max;
                        max_x_move = std::get<0>(copy_get_opponent_unit[j]);
                        max_y_move = std::get<1>(copy_get_opponent_unit[j]);
                        distance_reel = min;
                        nb_ennemie_adj_tot = nb_unit_adj;
                    }
                } 
            }        
            //std::cerr<<"finrrrr"<<max_x_move<<"/"<<max_y_move<<"/"<<distance_reel<<"/"<<nb_ennemie_adj_tot<<"\n";
            std::get<0>(best_position) = max_x_move;
            std::get<1>(best_position) = max_y_move;
            std::get<2>(best_position) = distance_reel;
            std::get<3>(best_position) = nb_ennemie_adj_tot;
        }

        bool verif_array_remove(const int x, const int y, std::vector<Position> &position_remove_best_alliee)
        {
            int compteur_1 = 0;
            for(int i = 0; i < position_remove_best_alliee.size();i++){
                if(x == position_remove_best_alliee[i].x && y == position_remove_best_alliee[i].y){compteur_1++;}}
            
            int compteur = 0;
            for(int i = 0; i < entities.get_my_unit().size();i++){
                if(x == entities.get_my_unit()[i].x && y == entities.get_my_unit()[i].y){compteur++;}
            }

            if(compteur_1 == compteur){return true;}
            else{return false;}

            /*for(int i = 0; i < position_remove_best_alliee.size();i++)
            {
                if(x == position_remove_best_alliee[i].x && y == position_remove_best_alliee[i].y){return true;}
            }
            return false;*/
        }

        bool verif_pos_is_in_arraySaveDist(bool get_dist,const int x,const int y,std::vector<std::tuple<int,int,int,int,int>> &save_dist, int &dist,int &getx,int &gety){
            if(get_dist == true){
                for(int i = 0; i < save_dist.size();i++){
                    if(x == std::get<0>(save_dist[i]) && y == std::get<1>(save_dist[i])){dist = std::get<2>(save_dist[i]);getx = std::get<3>(save_dist[i]);gety = std::get<4>(save_dist[i]); break;}
                } 
                return false;//ne veux rien dire pour ce cas...
            }
            else{
                for(int i = 0; i < save_dist.size();i++){
                    if(x == std::get<0>(save_dist[i]) && y == std::get<1>(save_dist[i])){return true;}
                }
                return false;
            }
        }

        void repartir_allie_on_unit_ennemie(std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie)
        {
            std::tuple<int, int, int,int> best_position_ennemie = std::make_tuple(-1, -1, -1,-1);//x,y,dist,nb_ennemie(+adj)
            std::vector<std::vector<std::tuple<int,int,int>>> save_dist_ennemie;
            auto started = std::chrono::high_resolution_clock::now();
            while(true){
                int compteur = 0;
                std::vector<std::tuple<int,int,int,int,int>> save_dist;//x,y,dist
                int get_dist = 0;
                bool leave_loop = false;
                //std::cerr<<"ok\n";
                //Recup ennemie le plus dangereux
                evaluation_ennemie_unit(position_to_dodge,position_remove_best_ennemie,best_position_ennemie,save_dist_ennemie);
                //std::cerr<<"ok1\n";
                if(std::get<0>(best_position_ennemie) == -1 && std::get<1>(best_position_ennemie) == -1){break;}
                //Enregistrer dans array pour ne pas le reselectionner
                position_remove_best_ennemie.push_back(Position(std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie)));
                //traiter un ennemie
                for(int j = 1; j <= std::get<3>(best_position_ennemie);j++)
                {
                    int min = 10000;
                    int x_best = -1;
                    int y_best = -1;
                    int origine_x = -1;
                    int origine_y = -1;
                    auto My_unit = entities.get_my_unit();
                    for(int i = 0; i < My_unit.size();i++){
                        if(verif_array_remove(My_unit[i].x,My_unit[i].y,position_remove_best_alliee))
                            {continue;}

                        int x,y;
                        if(!verif_pos_is_in_arraySaveDist(false,My_unit[i].x,My_unit[i].y,save_dist,get_dist,x,y)){
                            //std::cerr<<"not save\n";
                            //Recherche chemin
                            graphe.init_research_court_chemin(My_unit[i].x, My_unit[i].y, std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie), 1,position_to_dodge);
                            graphe.loop_search_chemin();
                            get_dist = graphe.get_list_chemin().size();
                            for(auto Position :graphe.get_list_chemin()){
                                x = Position.x;
                                y = Position.y;
                                break;
                            }
                            graphe.clear_list();
                            //Save dans list
                            save_dist.push_back(std::make_tuple(My_unit[i].x,My_unit[i].y,get_dist,x,y));
                        }
                        else{
                            verif_pos_is_in_arraySaveDist(true,My_unit[i].x,My_unit[i].y,save_dist,get_dist,x,y);
                            //std::cerr<<"ici:::"<<My_unit[i].x<<"/"<<My_unit[i].y<<"//"<<x<<"/"<<y<<"\n";
                        }
                        //int dist = distance(My_unit[i].x, My_unit[i].y, std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie));
                        if(get_dist != 0){
                            if(get_dist < min){
                                min = get_dist;
                                x_best = x;//My_unit[i].x;//x;
                                y_best = y;// My_unit[i].y;//y;
                                origine_x = My_unit[i].x;
                                origine_y = My_unit[i].y;
                            }
                        }
                    }
                    if(x_best == -1 && y_best == -1){
                        array_move_ennemie.push_back(std::make_tuple(std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie),std::get<3>(best_position_ennemie) - compteur,std::get<2>(best_position_ennemie)));
                        //leave_loop = true;
                        //std::cerr<<"1\n";
                        break;
                    }
                    else{
                        //array_move_allie.push_back(std::make_tuple(1,x_best,y_best,std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie)));
                        array_move_allie.push_back(std::make_tuple(1,origine_x,origine_y,x_best,y_best));
                        //position_remove_best_alliee.push_back(Position(x_best,y_best));
                        position_remove_best_alliee.push_back(Position(origine_x,origine_y));
                        compteur++;
                        //std::cerr<<"2\n";
                    }
                    if(j == std::get<3>(best_position_ennemie)){
                        array_move_ennemie.push_back(std::make_tuple(std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie),std::get<3>(best_position_ennemie) - j,std::get<2>(best_position_ennemie)));
                    }
                }
                //if(leave_loop == true){break;}
            }
            auto done = std::chrono::high_resolution_clock::now();
            std::string s = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count());
            // std::cerr<<"temps into repartir ennemie-------------- : "<<s<<std::endl;
            //Prendre le reste des unite dispo si il y en a et prendre l'avantage
            if(position_remove_best_alliee.size() != entities.get_my_unit().size()){
                //std::cerr<<"test : 2\n";
                for(int j = 0; j<array_move_ennemie.size();j++){
                    //std::cerr<<"test : 3\n";
                    if(std::get<2>(array_move_ennemie[j]) == 0){
                        //std::cerr<<"test : 5\n";
                        int min = 10000;
                        int x_best = -1;
                        int y_best = -1;
                        int origine_x = -1;
                        int origine_y = -1;
                        auto My_unit = entities.get_my_unit();
                        for(int i = 0; i < My_unit.size();i++){
                            if(verif_array_remove(My_unit[i].x,My_unit[i].y,position_remove_best_alliee))
                                {continue;}
                                
                            graphe.init_research_court_chemin(My_unit[i].x, My_unit[i].y, std::get<0>(array_move_ennemie[j]),std::get<1>(array_move_ennemie[j]), 1,position_to_dodge);
                            graphe.loop_search_chemin();
                            int dist = graphe.get_list_chemin().size();//distance(My_unit[i].x, My_unit[i].y, std::get<0>(array_move_ennemie[j]),std::get<1>(array_move_ennemie[j]));//
                            int x,y;
                            for(auto Position :graphe.get_list_chemin()){
                                x = Position.x;
                                y = Position.y;
                                break;
                            }
                            //std::cerr<<x<<"/"<<y<<std::endl;
                            graphe.clear_list();
                            //int dist = distance(My_unit[i].x, My_unit[i].y, std::get<0>(array_move_ennemie[j]),std::get<1>(array_move_ennemie[j]));
                            if(dist != 0){
                                //std::cerr<<"sdfdf\n";
                                if(dist < min){
                                    min = dist;
                                    x_best = x;//My_unit[i].x;
                                    y_best = y;//My_unit[i].y;
                                    origine_x = My_unit[i].x;
                                    origine_y = My_unit[i].y;
                                }
                            }
                        }
                        if(x_best != -1 && y_best != -1){
                            //array_move_allie.push_back(std::make_tuple(1,x_best,y_best,std::get<0>(array_move_ennemie[j]),std::get<1>(array_move_ennemie[j])));
                            array_move_allie.push_back(std::make_tuple(1,origine_x,origine_y,x_best,y_best));
                            //position_remove_best_alliee.push_back(Position(x_best,y_best));
                            position_remove_best_alliee.push_back(Position(origine_x,origine_y));
                            std::get<2>(array_move_ennemie[j]) = -1;
                            //std::cerr<<"test : 4\n";
                        }
                    }
                }
            }
            //std::cerr<<"finish\n";
        }

        void move_capture(std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie)
        {
            std::tuple<int, int, int> best_position_global = std::make_tuple(-1, -1, -1);//x,y,dist,nb_ennemie(+adj)
            std::vector<Position> array_remove_global;
            while(true){
                //Chercher case plus proche pour capture
                //std::cerr<<"move capture 1 en\n";
                calcule_min_distance_entre_my_unit_cellBoard(position_remove_best_alliee,array_remove_global,best_position_global);
                //std::cerr<<"move capture 2 en\n";
                if(std::get<0>(best_position_global) == -1 && std::get<1>(best_position_global) == -1){break;}
                
                int min = 10000;
                int x_best = -1;
                int y_best = -1;
                int origine_x = -1;
                int origine_y = -1;
                auto My_unit = entities.get_my_unit();
                for(int i = 0; i < My_unit.size();i++){
                    if(verif_array_remove(My_unit[i].x,My_unit[i].y,position_remove_best_alliee))
                        {continue;}

                    int x,y;
                    //Recherche chemin
                    graphe.init_research_court_chemin(My_unit[i].x, My_unit[i].y, std::get<0>(best_position_global),std::get<1>(best_position_global), 1,position_to_dodge);
                    graphe.loop_search_chemin();
                    int dist = graphe.get_list_chemin().size();
                    for(auto Position :graphe.get_list_chemin()){
                        x = Position.x;
                        y = Position.y;
                        break;
                    }
                    graphe.clear_list();
                    
                    //int dist = distance(My_unit[i].x, My_unit[i].y, std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie));
                    if(dist != 0){
                        if(dist < min){
                            min = dist;
                            x_best = x;//My_unit[i].x;//x;
                            y_best = y;// My_unit[i].y;//y;
                            origine_x = My_unit[i].x;
                            origine_y = My_unit[i].y;
                        }
                    }
                }
                if(x_best != -1 && y_best != -1){
                    //array_move_allie.push_back(std::make_tuple(1,x_best,y_best,std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie)));
                    array_move_allie.push_back(std::make_tuple(1,origine_x,origine_y,x_best,y_best));
                    //position_remove_best_alliee.push_back(Position(x_best,y_best));
                    position_remove_best_alliee.push_back(Position(origine_x,origine_y));
                    //Enregistrer dans array pour ne pas le reselectionner
                    array_remove_global.push_back(Position(std::get<0>(best_position_global),std::get<1>(best_position_global)));
                    //std::cerr<<"capturer\n";
                }
                else
                {
                    array_remove_global.push_back(Position(std::get<0>(best_position_global),std::get<1>(best_position_global)));
                }
            }
        }

        void move_capture_empty(std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie){
            std::tuple<int, int, int> best_position_global = std::make_tuple(-1, -1, -1);//x,y,dist,nb_ennemie(+adj)
            std::vector<Position> array_remove_global;
            while(true){
                //Chercher case plus proche pour capture
                //std::cerr<<"move capture 1 neutre\n";
                calcule_min_distance_entre_my_unit_cellBoard_empty(position_remove_best_alliee,array_remove_global,best_position_global);
                //std::cerr<<"move capture 2 neutre\n";
                if(std::get<0>(best_position_global) == -1 && std::get<1>(best_position_global) == -1){break;}
                
                int min = 10000;
                int x_best = -1;
                int y_best = -1;
                int origine_x = -1;
                int origine_y = -1;
                auto My_unit = entities.get_my_unit();
                for(int i = 0; i < My_unit.size();i++){
                    if(verif_array_remove(My_unit[i].x,My_unit[i].y,position_remove_best_alliee))
                        {continue;}

                    int x,y;
                    //Recherche chemin
                    graphe.init_research_court_chemin(My_unit[i].x, My_unit[i].y, std::get<0>(best_position_global),std::get<1>(best_position_global), 1,position_to_dodge);
                    graphe.loop_search_chemin();
                    int dist = graphe.get_list_chemin().size();
                    for(auto Position :graphe.get_list_chemin()){
                        x = Position.x;
                        y = Position.y;
                        break;
                    }
                    graphe.clear_list();
                    
                    //int dist = distance(My_unit[i].x, My_unit[i].y, std::get<0>(best_position_global),std::get<1>(best_position_global));
                    if(dist != 0){
                        if(dist < min){
                            min = dist;
                            x_best = x;//My_unit[i].x;//x;
                            y_best = y;//My_unit[i].y;//y;
                            origine_x = My_unit[i].x;
                            origine_y = My_unit[i].y;
                        }
                    }
                }
                if(x_best != -1 && y_best != -1){
                    //array_move_allie.push_back(std::make_tuple(1,x_best,y_best,std::get<0>(best_position_global),std::get<1>(best_position_global)));
                    array_move_allie.push_back(std::make_tuple(1,origine_x,origine_y,x_best,y_best));
                    //position_remove_best_alliee.push_back(Position(x_best,y_best));
                    position_remove_best_alliee.push_back(Position(origine_x,origine_y));
                    //Enregistrer dans array pour ne pas le reselectionner
                    array_remove_global.push_back(Position(std::get<0>(best_position_global),std::get<1>(best_position_global)));
                    //std::cerr<<"capturer neutre\n";
                }
                else
                {
                    array_remove_global.push_back(Position(std::get<0>(best_position_global),std::get<1>(best_position_global)));
                }
            }
        }

        void coordinatination_action(std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<Position> &array_spawn,std::vector<Position> &array_recycler)
        {
            //Add : faire en sorte de faire eventuellement plus fois early game , spawn quand plus ennemie sur case allie
            std::vector<std::tuple<int,int,int,int>> array_move_ennemie;//x,y,nombre restant(0 egalite, 1,2...-> manque 2, -1 un de plus),dist plus proche avec case allie
            std::vector<Position> position_to_dodge;//x,y, allie
            remplir_array_position_en_or_all_dangereux(false,position_to_dodge);//case a eviter pour les alliee
            std::vector<Position> position_remove_best_ennemie;//x,y
            std::vector<Position> position_remove_best_alliee;//x,y

            auto started = std::chrono::high_resolution_clock::now();
            //Fonction de built les plus evident pour les recyclers
            construct_recycler_early_game(array_recycler,array_spawn,position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            constrcut_recycler_defense(array_recycler,array_spawn,position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            auto done = std::chrono::high_resolution_clock::now();
            std::string s = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count());
            // std::cerr<<"temps-------------- : "<<s<<std::endl;

            auto started_2 = std::chrono::high_resolution_clock::now();
            //Fonction pour les move de defenses
            repartir_allie_on_unit_ennemie(position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            auto done_2 = std::chrono::high_resolution_clock::now();
            std::string s_2 = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done_2-started_2).count());
            // std::cerr<<"temps-------------- : "<<s_2<<std::endl;

            auto started_3 = std::chrono::high_resolution_clock::now();
            //Spawn (si dans les spawn je vois que meme en mettant les spwan, j ai pas assez (ennemie distance 1), ceux deja mis sont reallouer pour aller faire le move de capture, à la place on fera des built)
            spawn_defense(array_spawn,position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            auto done_3 = std::chrono::high_resolution_clock::now();
            std::string s_3 = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done_3-started_3).count());
            // std::cerr<<"temps-------------- : "<<s_3<<std::endl;

            auto started_4 = std::chrono::high_resolution_clock::now();
            //Spawn prendre avantage
            spawn_to_take_advantages(array_spawn,position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            auto done_4 = std::chrono::high_resolution_clock::now();
            std::string s_4 = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done_4-started_4).count());
            // std::cerr<<"temps-------------- : "<<s_4<<std::endl;

            //Built de secour sur ceux qui etait impossibel(ces ennemie sera forcement a une distance de 1)
            //...

            auto started_5 = std::chrono::high_resolution_clock::now();
            //move de capture ennemie
            move_capture(position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            auto done_5 = std::chrono::high_resolution_clock::now();
            std::string s_5 = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done_5-started_5).count());
            // std::cerr<<"temps-------------- : "<<s_5<<std::endl;

            auto started_6 = std::chrono::high_resolution_clock::now();
            //move de capture case vide
            move_capture_empty(position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            auto done_6 = std::chrono::high_resolution_clock::now();
            std::string s_6 = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done_6-started_6).count());
            // std::cerr<<"temps-------------- : "<<s_6<<std::endl;

            auto started_7 = std::chrono::high_resolution_clock::now();
            //Spawn et built si il reste des ressources
            spawn_to_take_must_advantages(array_spawn,position_remove_best_alliee,position_remove_best_ennemie,position_to_dodge,array_move_allie,array_move_ennemie);
            auto done_7 = std::chrono::high_resolution_clock::now();
            std::string s_7 = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done_7-started_7).count());
            // std::cerr<<"temps-------------- : "<<s_7<<std::endl;
        }

        void to_do_action()
        {
            auto started = std::chrono::high_resolution_clock::now();
            bool action = false;
            std::vector<std::tuple<int, int, int,int,int>> array_move_allie;//amount,x,y,x_dest,y_dest
            std::vector<Position> array_spawn;
            std::vector<Position> array_recycler;
            //tableau pour les spawn et les built...
            //...

            //Appel fonction coordonnate pour la coor des action et le remplissage des coup a jouer...
            coordinatination_action(array_move_allie,array_spawn,array_recycler);

            //Command pour faire les actions
            //Construction
            for (int i = 0; i < array_recycler.size(); i++)
            {
                Command recycler(Command::BUILD, 1, -1,-1,-1,-1,array_recycler[i].x, array_recycler[i].y);
                action = true;
            }
            //construct_recycler_early_game(action);
            //Spawn
            for (int i = 0; i < array_spawn.size(); i++)
            {
                Command spawn(Command::SPAWN, 1, -1,-1,-1,-1,array_spawn[i].x, array_spawn[i].y);
                action = true;
            }
            
            //Move defense
            for (int i = 0; i < array_move_allie.size(); i++)
            {
                Command move(Command::MOVE,std::get<0>(array_move_allie[i]), std::get<1>(array_move_allie[i]), std::get<2>(array_move_allie[i]), std::get<3>(array_move_allie[i]), std::get<4>(array_move_allie[i]), -1, -1);
                action = true;
            }
            //Wait
            if(!action)
            {
                Command waitCommand(Command::WAIT);
            }
            //Message info
            auto done = std::chrono::high_resolution_clock::now();
            std::string s = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count());
            Command messageCommand(Command::MESSAGE,s);
            std::cerr<<s<<std::endl;
            //Fin message
            std::cout << std::endl; 
        }

        void constrcut_recycler_defense(std::vector<Position> &array_recycler,std::vector<Position> &array_spawn,std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie){
            for(int i = 0; i < board.get_my_cells().size();i++)
            {
                if(board.get_my_cells()[i].can_build == 1 && data.my_matter >= 10)
                {
                    bool verif = false;
                    int x_origine = board.get_my_cells()[i].x;
                    int y_origine = board.get_my_cells()[i].y;
                    for(int j = 0; j < 8; j++)
                    {
                        if(board.get_my_cells()[i].neighbours[j].is_exist == true){
                            int x_voisin = board.get_board()(x_origine,y_origine).neighbours[j].x;
                            int y_voisin = board.get_board()(x_origine,y_origine).neighbours[j].y;
                            if(j == 1 || j == 3 || j == 4 || j == 6)//pas les diagonnales
                            {
                                if(board.get_board()(x_voisin,y_voisin).units > 0 && board.get_board()(x_voisin,y_voisin).owner == 0){verif = true;break;}
                            }
                        } 
                    }
                    if(verif){
                    position_to_dodge.push_back(Position(board.get_my_cells()[i].x,board.get_my_cells()[i].y));
                    array_recycler.push_back(Position(board.get_my_cells()[i].x,board.get_my_cells()[i].y));
                    data.my_matter -=10;
                    }//std::cerr<<"recyclr ok "<<board.get_my_cells()[i].x<<"/"<<board.get_my_cells()[i].y<<std::endl;}
                }        
            }
        }

        void construct_recycler_early_game(std::vector<Position> &array_recycler,std::vector<Position> &array_spawn,std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie)//rajout tableau coor fait pour que les autre sache qu il ne faut pas joueur la
        {
            const auto& My_cell =  board.get_my_cells();
            const auto& array_global = board.get_board();
            bool present = false;
            for(int i = 0; i < board.get_my_cells().size();i++){
                if(within_cell_opp_around_version2(My_cell[i].x,My_cell[i].y)){present = true;break;}}

            if(present){global_fin_early = true;}
            //std::cerr<<"recyclr early "<<present<<std::endl;
            if(!present && data.my_matter >=10 && !global_fin_early && ((data.my_matter) - old_ressources) >= 20){
                int max = -111;
                int x = -1;
                int y = -1;
                //std::cerr<<"ok "<<std::endl;
                for(int i = 0; i < My_cell.size();i++){
                    //std::cerr<<"my recycler "<<My_cell[i].x<<"/"<<My_cell[i].y<<std::endl;
                    if(My_cell[i].recycler != 1 && My_cell[i].units == 0 && My_cell[i].scrap_amount > 1){
                        //std::cerr<<"my recycler "<<My_cell[i].x<<"/"<<My_cell[i].y<<std::endl;
                        int scrapt_amount_ = My_cell[i].scrap_amount;
                        int score = scrapt_amount_; 
                        //Note case voisine
                        for(int j = 0; j < 8; j++){
                            if(j == 1 || j == 3 || j == 4 || j == 6){
                                int x_voisin = My_cell[i].neighbours[j].x;
                                int y_voisin = My_cell[i].neighbours[j].y;
                                //std::cerr<<"nombre : "<<array_global(x_voisin,y_voisin).scrap_amount<< "compare base /"<<scrapt_amount_<<std::endl;
                                //Analyse case
                                if(array_global(x_voisin,y_voisin).scrap_amount == 0){
                                    score -= scrapt_amount_;
                                }
                                else if(array_global(x_voisin,y_voisin).scrap_amount > scrapt_amount_){
                                    score -= (array_global(x_voisin,y_voisin).scrap_amount - scrapt_amount_);
                                }
                                else if(array_global(x_voisin,y_voisin).scrap_amount < scrapt_amount_){
                                    score += (scrapt_amount_ - array_global(x_voisin,y_voisin).scrap_amount);
                                }
                                else{
                                    score -= 4;
                                }
                            }
                        }
                        if(score > max){
                            max = score;
                            x = My_cell[i].x;
                            y = My_cell[i].y;
                            //std::cerr<<"max "<< max<<"x :"<<x<<"/"<<y<<std::endl;
                        }
                    }
                }
                if(x != -1 && y != -1){
                    position_to_dodge.push_back(Position(x,y));
                    array_recycler.push_back(Position(x,y));
                    data.my_matter -=10;
                    //std::cerr<<"recyclr ok "<<x<<"/"<<y<<std::endl;
                }
                old_ressources = data.my_matter; 
            }
        }

        bool present_dodge_tab(int x,int y,std::vector<Position> &position_to_dodge){
            for(int i = 0; i < position_to_dodge.size();i++){
                if(x == position_to_dodge[i].x && y == position_to_dodge[i].y){return true;}
            }
            return false;
        }

        void spawn_defense(std::vector<Position> &array_spawn,std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie){
            for(int i = 0; i < array_move_ennemie.size();i++){
                //std::cerr<<"affcihage spawn tab x: "<<std::get<0>(array_move_ennemie[i])<<"/y :"<<std::get<1>(array_move_ennemie[i])<<"/ nb :"<<std::get<2>(array_move_ennemie[i])<<std::endl;
                if(std::get<2>(array_move_ennemie[i]) > 0 && data.my_matter >= 10){
                    for(int j = 0; j < std::get<2>(array_move_ennemie[i]);j++){
                        int min = 10000;
                        int origine_x = -1;
                        int origine_y = -1;
                        auto My_unit = board.get_my_cells();
                        for(int p = 0; p < My_unit.size();p++){
                            if(My_unit[p].recycler == 1 || !within_cell_opp_around(My_unit[p].x, My_unit[p].y) || present_dodge_tab(My_unit[p].x, My_unit[p].y,position_to_dodge))
                                {continue;}

                            //Recherche chemin
                            graphe.init_research_court_chemin(My_unit[p].x, My_unit[p].y, std::get<0>(array_move_ennemie[i]),std::get<1>(array_move_ennemie[i]), 1,position_to_dodge);
                            graphe.loop_search_chemin();
                            int dist = graphe.get_list_chemin().size();
                            graphe.clear_list();
                            //int dist = distance(My_unit[p].x, My_unit[p].y, std::get<0>(array_move_ennemie[i]),std::get<1>(array_move_ennemie[i]));
                            if(dist != 0){
                                if(dist < min){
                                    min = dist;
                                    origine_x = My_unit[p].x;
                                    origine_y = My_unit[p].y;
                                }
                            }
                        }
                        if(origine_x != -1 && origine_y != -1){
                            //array_move_allie.push_back(std::make_tuple(1,x_best,y_best,std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie)));
                            array_spawn.push_back(Position(origine_x,origine_y));
                            std::get<2>(array_move_ennemie[i]) -= 1;
                            //std::cerr<<"spawn defense effectue\n";
                            data.my_matter -= 10;}}}
            }
        }

        void spawn_to_take_advantages(std::vector<Position> &array_spawn,std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie){
            for(int i = 0; i < array_move_ennemie.size();i++){
                //std::cerr<<"affcihage spawn take advantages tab x: "<<std::get<0>(array_move_ennemie[i])<<"/y :"<<std::get<1>(array_move_ennemie[i])<<"/ nb :"<<std::get<2>(array_move_ennemie[i])<<std::endl;
                if(std::get<2>(array_move_ennemie[i]) == 0 && data.my_matter >= 10){
                    //for(int j = 0; j > -1;j--){
                        int min = 10000;
                        int origine_x = -1;
                        int origine_y = -1;
                        auto My_unit = board.get_my_cells();
                        for(int p = 0; p < My_unit.size();p++){
                            if(My_unit[p].recycler == 1 || !within_cell_opp_around(My_unit[p].x, My_unit[p].y)|| present_dodge_tab(My_unit[p].x, My_unit[p].y,position_to_dodge))
                                {continue;}

                            //Recherche chemin
                            graphe.init_research_court_chemin(My_unit[p].x, My_unit[p].y, std::get<0>(array_move_ennemie[i]),std::get<1>(array_move_ennemie[i]), 1,position_to_dodge);
                            graphe.loop_search_chemin();
                            int dist = graphe.get_list_chemin().size();
                            graphe.clear_list();
                            //int dist = distance(My_unit[p].x, My_unit[p].y, std::get<0>(array_move_ennemie[i]),std::get<1>(array_move_ennemie[i]));
                            if(dist != 0){
                                if(dist < min){
                                    min = dist;
                                    origine_x = My_unit[p].x;
                                    origine_y = My_unit[p].y;
                                }
                            }
                        }
                        if(origine_x != -1 && origine_y != -1){
                            //array_move_allie.push_back(std::make_tuple(1,x_best,y_best,std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie)));
                            array_spawn.push_back(Position(origine_x,origine_y));
                            std::get<2>(array_move_ennemie[i]) -= 1;
                            //std::cerr<<"spawn defense effectue\n";
                            data.my_matter -= 10;}}//}
            }
        }

        void spawn_to_take_must_advantages(std::vector<Position> &array_spawn,std::vector<Position> &position_remove_best_alliee, std::vector<Position> &position_remove_best_ennemie,std::vector<Position> &position_to_dodge,std::vector<std::tuple<int, int, int,int,int>> &array_move_allie,std::vector<std::tuple<int,int,int,int>> &array_move_ennemie){
            for(int i = 0; i < array_move_ennemie.size();i++){
                //std::cerr<<"affcihage spawn must_advantage tab x: "<<std::get<0>(array_move_ennemie[i])<<"/y :"<<std::get<1>(array_move_ennemie[i])<<"/ nb :"<<std::get<2>(array_move_ennemie[i])<<std::endl;
                if(std::get<2>(array_move_ennemie[i]) < 0 && data.my_matter >= 20){
                    //for(int j = 0; j > std::get<2>(array_move_ennemie[i]);j--){
                        int min = 10000;
                        int origine_x = -1;
                        int origine_y = -1;
                        auto My_unit = board.get_my_cells();
                        for(int p = 0; p < My_unit.size();p++){
                            if(My_unit[p].recycler == 1 || !within_cell_opp_around(My_unit[p].x, My_unit[p].y)|| present_dodge_tab(My_unit[p].x, My_unit[p].y,position_to_dodge))
                                {continue;}

                            //Recherche chemin
                            graphe.init_research_court_chemin(My_unit[p].x, My_unit[p].y, std::get<0>(array_move_ennemie[i]),std::get<1>(array_move_ennemie[i]), 1,position_to_dodge);
                            graphe.loop_search_chemin();
                            int dist = graphe.get_list_chemin().size();
                            graphe.clear_list();
                            //int dist = distance(My_unit[p].x, My_unit[p].y, std::get<0>(array_move_ennemie[i]),std::get<1>(array_move_ennemie[i]));
                            if(dist != 0){
                                if(dist < min){
                                    min = dist;
                                    origine_x = My_unit[p].x;
                                    origine_y = My_unit[p].y;
                                }
                            }
                        }
                        if(origine_x != -1 && origine_y != -1){
                            //array_move_allie.push_back(std::make_tuple(1,x_best,y_best,std::get<0>(best_position_ennemie),std::get<1>(best_position_ennemie)));
                            array_spawn.push_back(Position(origine_x,origine_y));
                            std::get<2>(array_move_ennemie[i]) -= 1;
                            //std::cerr<<"spawn defense effectue\n";
                            data.my_matter -= 10;}}//}
            }
        }

        void basic_strat()
        {
            to_do_action();
        }
};

#ifndef TESTING
int main(){
    std::ios_base::sync_with_stdio(false);
    
    //----------------------------------NOUVEAU----------------------------------//
    Board board;
    IA ia(board);
    while(1)
    {
        ia.loop_game();
    }
    return 0;
}
#endif
