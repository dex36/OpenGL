// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <map>
#include <vector>
#include <stack>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <memory>
#include <mutex>
using namespace std;


/**

void f(const vector<int>& vec, int x)
{
	cout << "Liczba wartości mniejszych niż " << x
		<< ": " << count(vec, [&](int a){ return a<x; }) /// jezeli dajemy w pred(x) to wrzuca nam tego x w (int x)
		<< '\n';
}

template<typename C, typename P>
int count(const C& c, P pred)
{
	int cnt = 0;
	for (const auto& x : c)
		if (pred(x))
			++cnt;
	return cnt;
}

int main()
{
	vector <int> vectorek{ 1, 3, 4, 5, 6 };

	f(vectorek, 5);

	system("pause");
	
}


vector<string::iterator> find_all2(string& c, char v) // znajduje wszystkie wystąpienia v w c
{
	vector<string::iterator> res;
	for (auto p = c.begin(); p != c.end(); ++p)
		if (*p == v)
			res.push_back(p);
	return res;
}

int main(int argc, char* argv[]){
	
	vector <int> ada{ 1, 2, 3, 4, 5 };
	auto ab = find_all2(ada, 1);


	system("pause");
}


struct F {
	void operator()() { 
		for (int i = 0; i >-100; i--){
			cout << "from t1" << i << endl;
		}
	}
};
int main(){


		thread t1{ F() }; // F()() działa w osobnym wątku

		
			for (int i = 0; i < 100; i++){
				cout << "from main" << i << endl;
			}
		
		
		t1.join(); // czeka na t1
       
		system("pause");
}
**/
/**

int main(){
	enum class Flag : char
	{
		print=1,
		show=2,

	};
	int a;
	Flag whattodo;
	cin >> a;
	if (a == 1){
		whattodo = Flag::print;
	}
	else
	{
		whattodo = Flag::show;
	}

	switch (whattodo){
		case Flag::print:
			cout << "print";
			break;
		case Flag::show:
			cout << "show";
			break;
	}

	system("pause");
}
**/
/**
class Date {
public:
	Date& add_year(int n); // dodaje n lat
	Date& add_month(int n); // dodaje n miesięcy
	Date& add_day(int n); // dodaje n dni
private:
	int y, x, z;
};
Date& Date::add_year(int n)
{
	y += n;
	return*this;
}

Date& Date::add_month(int n)
{
	x += n;
	return*this;
}

Date& Date::add_day(int n)
{
	z += n;
	return*this;
}
void f(Date& d)
{
	//...
	d.add_day(1).add_month(1).add_year(1);
	//...
}
int main(){
	Date nowa;
	f(nowa);


	system("pause");
}
**/
/**

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity;
int minex, miney;
int score;
int tailx[100], taily[100];
int ntail;
bool printmine;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN, CREATE};
eDirection dir;
void Setup(){
	gameOver = false;
	dir = STOP;
	x = 1;
	y = 1;
	fruitx = width/2;
	fruity = height/2;
	score = 0;
}
void movingFruit(){
	
		if (_kbhit())
		{
			int fruitprevx, fruitprevy;
			fruitprevx = fruitx;
			fruitprevy = fruity;
			fruitx += (std::rand() % -1) + 1;
			fruity += (std::rand() % -1) + 1;
			if (fruitx > width || fruitx < 0 || fruity > height || fruity < 0){
				fruity = fruitprevx;
				fruitx = fruitprevy;
			}
		}
	
}

void Draw(){
	system("cls");
	for (int i = 0; i < width+2; i++){
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruity && j == fruitx)
				cout << "P";

			else 
			{
				bool print = false;
				for (int k = 0; k < ntail; k++){
					if (tailx[k] == j && taily[k] == i){
						cout << "o";
						print = true;
					}
				}
				if (i == miney && j == minex){
					cout << "X";
					print = true;
				}
				if (!print){
					cout << " ";
				}
			}
	
			
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; i++){
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score;
}

void Input(){
	if (_kbhit()){
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT; 
			break;
		case 'w':
			dir = UP; 
			break;
		case 's':
			dir = DOWN; 
			break;
		case 'e':
			dir = CREATE;
			break;
		case 'x':
			gameOver = true; 
			break;

		}
	}
}

void Logic(){
	
	int prevX = tailx[0];
	int prevY = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < ntail; i++){
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevX;
		taily[i] = prevY;
		prevX = prev2x;
		prevY = prev2y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case CREATE:
		minex = x;
		miney = y;
		break;
	
	}
	if (x > width || x < 0 || y > height || y<0 ){
		gameOver = true;
	}
	if (x == fruitx && y == fruity){
		score += 10;
		ntail++;
	}



}

int main()
{
	
		Setup();
		while (!gameOver){
			Draw();
			movingFruit();
			Input();
			Logic();
		}

		return 0;
	
}**/
/**

#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector

using namespace std;

atomic<bool> ready(false);
atomic_flag winner;

void liczenie(int id) {
	while (!ready) { this_thread::yield(); }  // wait for the ready signal
	for (volatile int i = 0; i<1000000; ++i) {}          // go!, count to 1 million
	//if (!winner.test_and_set()) { cout << "thread #" << id << " won!\n"; }
	if (!std::atomic_flag_test_and_set_explicit(&winner, std::memory_order_acquire)) { cout << "thread #" << id << " won!\n"; }

};

int main()
{
	vector<thread> threads;

	for (int i = 1; i <= 10; ++i) 
	threads.push_back(thread(liczenie, i));

	ready = true;
	for (auto& th : threads) th.join();
	
	return 0;
}**/
// duration::zero
/**
#include <iostream>
#include <chrono>

int main()
{
	using std::chrono::system_clock;

	system_clock::time_point t1 = system_clock::now();

	for (int i = 0; i < 5000; i++)
	{
		std::cout << "mocaz \n";
	}
	system_clock::time_point t2 = system_clock::now();

	system_clock::duration d = t2 - t1;

	if (d == system_clock::duration::zero())
		std::cout << "The internal clock did not tick.\n";

	else
		std::cout << "The internal clock advanced " << d.count() * system_clock::period::num / system_clock::period::den << " sec.\n";

	system("pause");
}**/
/**
#include <iostream>     // std::cout
#include <algorithm>    // std::all_of
#include <array>        // std::array
#include <sstream>  

template <typename FwdIterator>
void printArray(FwdIterator begin, FwdIterator end)
{
	while (begin != end) {
		std::cout << *begin << std::endl;
		begin++;
	}
}

int main() {
	std::array<int,2> foo = { 5, 5};
	printArray(foo.begin(), foo.end());

		
		int a;
		cin >> a;

	if (std::all_of(foo.begin(), foo.end(), [=](int i){return i % a; }))
		std::cout << " " << a << " ";

	system("pause");
}
**/
/**
// for_each example
#include <iostream>     // std::cout
#include <algorithm>    // std::for_each
#include <vector>       // std::vector

void myfunction(int i) {  // function:
	std::cout << ' ' << i;
}

class myclass {    
public: 
	void operator() (int i) { std::cout << ' ' << i; }
};

int main() 
{
	std::vector<int> myvector;
	myvector.push_back(10);
	myvector.push_back(20);
	myvector.push_back(30);

	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myfunction);
	std::cout << '\n';

	// or:
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myclass());
	std::cout << '\n';

	system("pause");
}**/
/**
#include <iostream>     // std::cout
using namespace std;
template <typename T, typename... R>
void printshit(T first, T second, R... rest){
	cout << first+second << ' ';
	printshit(rest...);
}
void printshit(){
	cout << endl;
}
int main(){
	printshit(1, 1, 1);
	
	system("pause");
	}**//**
#include <algorithm>    // std::find

int main(){
	std::vector<std::pair<int, int>> newest;
	std::vector<std::pair<int, int>>::iterator myIT;
	std::pair <int, int> productszukany(2, 1);

	for (int i = 0; i < 5; i++){
		std::pair <int, int> product(i+1, i);
		newest.push_back(product);
		
	}

	myIT = find(newest.begin(), newest.end(), productszukany);
	if (myIT != newest.end())
		cout << "Znalazlem";
	else
		cout << " chuja do dupy";

	system("pause");
}**/
/**
template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
{
	typename
		ForwardIterator1::pointer tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;

	iterator_traits<ForwardIterator1*> traits = tmp;
}**/
/**
class Layer{
public:
	Layer * next;
	int a;
};
void pushit(Layer *&mylayer, int score){

	Layer *p = new Layer;
	p->a = score;
	p->next = mylayer;
	mylayer = p;
}
void print(Layer *p){
	unsigned i;
	for (i = 1; p; p = p->next)
		cout << "Element #" << i++ << "  data = " << p->a << endl;
	cout << endl;
}
int  main(){
	Layer * L = NULL;
		pushit(L, 5);
		print(L);

		system("pause");
}**/
/**
int main(){

	map<int, int> mymap;
	map<int, int>::iterator it;
	int a = 5;
	for (auto i = 0; i < a; i++){
		for (auto j = 0; j < a; j++){
			mymap.insert(std::pair<int, int>(i, j));
		}
	}
	while (1){
		system("cls");
	for (it = mymap.begin(); it != mymap.end(); ++it){
		for (auto i = 0; i < a; i++){
			cout << it->first;
		}
		cout << endl;
	}
   }
	system("pause");
	}**//**
std::mutex mtx;           // mutex for critical section

void print_block(int n, char c) {
	// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx.lock();
	for (int i = 0; i<n; ++i) { std::cout << c; }
	std::cout << '\n';
	mtx.unlock();
}

int main()
{
	std::thread th1(print_block, 150, '*');
	std::thread th2(print_block, 150, '$');

	th1.join();
	th2.join();

	system("pause");
}**/
/**
#include <iostream>					// for cout etc.
#include <vector>					// for vector class
#include <string>					// for string class
#include <algorithm>				// for sort algorithm
#include <time.h>					// for random seed
#include <math.h>					// for abs()

#define GA_POPSIZE		2048		// ga population size
#define GA_MAXITER		16384		// maximum iterations
#define GA_ELITRATE		0.10f		// elitism rate
#define GA_MUTATIONRATE	0.25f		// mutation rate
#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
#define GA_TARGET		std::string("Adam malysz") 

using namespace std;				// polluting global namespace, but hey...

struct ga_struct
{
	string str;						// the string
	unsigned int fitness;			// its fitness
};

typedef vector<ga_struct> ga_vector;// for brevity

void init_population(ga_vector &population,ga_vector &buffer)
{
	int tsize = GA_TARGET.size();

	for (int i = 0; i<GA_POPSIZE; i++) {
		ga_struct citizen;

		citizen.fitness = 0;
		citizen.str.erase();

		for (int j = 0; j<tsize; j++)
			citizen.str += (rand() % 90) + 32;

		population.push_back(citizen);
	}

	buffer.resize(GA_POPSIZE);
}

void calc_fitness(ga_vector &population)
{
	string target = GA_TARGET;
	int tsize = target.size();
	unsigned int fitness;

	for (int i = 0; i<GA_POPSIZE; i++) {
		fitness = 0;
		for (int j = 0; j<tsize; j++) {
			fitness += abs(int(population[i].str[j] - target[j]));
		}

		population[i].fitness = fitness;
	}
}

bool fitness_sort(ga_struct x, ga_struct y)
{
	return (x.fitness < y.fitness);
}

inline void sort_by_fitness(ga_vector &population)
{
	sort(population.begin(), population.end(), fitness_sort);
}

void elitism(ga_vector &population,ga_vector &buffer, int esize)
{
	for (int i = 0; i<esize; i++) {
		buffer[i].str = population[i].str;
		buffer[i].fitness = population[i].fitness;
	}
}

void mutate(ga_struct &member)
{
	int tsize = GA_TARGET.size();
	int ipos = rand() % tsize;
	int delta = (rand() % 90) + 32;

	member.str[ipos] = ((member.str[ipos] + delta) % 122);
}

void mate(ga_vector &population, ga_vector &buffer)
{
	int esize = GA_POPSIZE * GA_ELITRATE;
	int tsize = GA_TARGET.size(), spos, i1, i2;

	elitism(population, buffer, esize);

	// Mate the rest
	for (int i = esize; i<GA_POPSIZE; i++) {
		i1 = rand() % (GA_POPSIZE / 2);
		i2 = rand() % (GA_POPSIZE / 2);
		spos = rand() % tsize;

		buffer[i].str = population[i1].str.substr(0, spos) +
			population[i2].str.substr(spos, esize - spos);

		if (rand() < GA_MUTATION) mutate(buffer[i]);
	}
}

inline void print_best(ga_vector &gav)
{
	cout << "Best: " << gav[0].str << " (" << gav[0].fitness << ")" << endl;
}

inline void swap(ga_vector *&population,
	ga_vector *&buffer)
{
	ga_vector *temp = population; population = buffer; buffer = temp;
}

int main()
{
	srand(unsigned(time(NULL)));

	ga_vector pop_alpha, pop_beta;
	ga_vector *population, *buffer;

	init_population(pop_alpha, pop_beta);
	population = &pop_alpha;
	buffer = &pop_beta;

	for (int i = 0; i<GA_MAXITER; i++) {
		calc_fitness(*population);		// calculate fitness
		sort_by_fitness(*population);	// sort them
		print_best(*population);		// print the best one

		if ((*population)[0].fitness == 0) break;

		mate(*population, *buffer);		// mate the population together
		swap(population, buffer);		// swap buffers
	}

	system("pause");
}

/**
#include <iostream>
#include <vector>
class myclass
{
public:
	myclass(int a) : a{ a } {}
	int a;
	static myclass*fun(int a);
};

myclass* myclass::fun(int a){
	myclass *newes = new myclass(a);
	return newes;
}

int main(){
	myclass* moja = myclass::fun(5);
	std::cout << moja->a << endl;
	system("pause");
}**///////////////////////////////////////////////////
/**
#include <iostream>
using namespace std;

class Point
{
private:
	double m_dX, m_dY, m_dZ;

public:
	Point(double dX = 0.0, double dY = 0.0, double dZ = 0.0)
	{
		m_dX = dX;
		m_dY = dY;
		m_dZ = dZ;
	}

	friend ostream& operator<< (ostream &out, Point &cPoint);
	friend istream& operator>> (istream &in, Point &cPoint);

	double GetX() { return m_dX; }
	double GetY() { return m_dY; }
	double GetZ() { return m_dZ; }
};

ostream& operator<< (ostream &out, Point &cPoint)
{
	// Since operator<< is a friend of the Point class, we can access
	// Point's members directly.
	out << "(" << cPoint.m_dX << ", " <<
		cPoint.m_dY << ", " <<
		cPoint.m_dZ << ")";
	return out;
}

istream& operator>> (istream &in, Point &cPoint)
{
	in >> cPoint.m_dX;
	in >> cPoint.m_dY;
	in >> cPoint.m_dZ;
	return in;
}

int main()
{
	using namespace std;
	cout << "Enter a point: " << endl;

	Point cPoint;
	cin >> cPoint;

	cout << "You entered: " << cPoint << endl;

	return 0;
}
**//////////////////////////////////////////////////
/**
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
template <typename T> // nSize is the expression parameter
T mnozy(const T& x){
	return x*x;
}
int main(){
	double pi = 3;
	mnozy(pi);
	system("pause");
}


template <typename T, typename T::type N>
struct SomeClass
{ };
struct S1
{
	typedef int type;
};
SomeClass<S1, 3> x;


template < double F(int)>
struct A
{ };

template<typename T, T VALUE> 
class Y
{ };
void mains(){
	Y<int, 7> y1; // fine
//	Y<double, 3.0> y2; // error: the constant '3' cannot have type
	reinterpret_cast<int>(p + 1);
}**/

//////////////////////////////////////////////////////
/**
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
template<long long N>
class first{
public:
	enum{value = N * first<N-1>::value};
};
template<>
class first < 0 > {
public:
	enum{value = 1};
};

class Pointer{
public:
	Pointer* next;
	int data;
};
class List{
public:
	Pointer* first;
	List operator++();
	void push(int d);
	void show(List &L);
};
void List::push(int d){
	Pointer* newPoint = new Pointer;
	newPoint->data = d;
	newPoint->next = first;
	first = newPoint;
}
void List::show(List &L){
	
	Pointer * current;
	current = L.first;
	while (current){
		cout << current->data;
		current = current->next;
	}
}
List List::operator++(){
	List newest;
	newest.first = first + 5;
	return (newest);
}

int main(){

	List nowa;
	nowa.push(1);
	nowa.push(2);
	nowa.push(2);
	nowa++;
	nowa.show(nowa);

	system("pause");
	int x = 5;
	if (34 < x < 47){}
}**/
/**
#include <iostream>
using namespace std;

template <typename T, typename CONTAINER = int>
struct typeindex{
	static const int value = 1;
};
template <typename T>
struct typeindex<T>
{
	static const int value = (-1);
};

class adam{};


int main(){

//	typeindex<int, char>::value;
	cout << typeindex<int, int>::value;
	system("pause");
}
**/
/**
#include <iostream>
using namespace std;
class Widget {
	double wgt; // Weight of the widget
	double *wgt2;
public:
	Widget(double w) : wgt(w) {}
	double weight() const { return wgt; }
	double & weight() { return wgt; }
	Widget & operator*=(float factor);
};

Widget & Widget::operator*=(float factor) {
	for (int i = 0; i < 3; i++)
		wgt2[i] *= factor;
	return *this;
}
int main(){
	Widget w(35);
	cout << w.weight();
	w.weight() = -6;
	cout << w.weight();
	system("pause");
}**/
/**
#include <iostream>
using namespace std;
template <class T> 
struct iterator_traits2{
	typedef T value_type2;
	//typedef typename T::value_type value_type;
};

template <class ForwardIterator1, class ForwardIterator2>
void iter_swap2(ForwardIterator1 i1, ForwardIterator2 i2)
{
	//typename ForwardIterator1::value_type tmp = *i1;
	typename iterator_traits2<ForwardIterator1>::value_type2 *tmp = &*i1;
	*i1 = *i2;
	*i2 = tmp;
}
void f(int* p1, int* p2)
{
	iter_swap2(p1, p2); // error: int* has no member 'value_type'
}
int main(){
	
	int *a = new int(6);
	int *b = new int(9);
	cout << *a;
	f(a, b);
	cout << *a;
	system("pause");
}**/
/**
template <typename X>
struct outer
{
	template <typename T>
	static T g(T x)
	{
		cout << "ale";
		return 1;
	}
};
template <typename X>
void do_it()
{
	typedef double(*FUNC_T)(double);
	FUNC_T f1 = outer<X>::g<double>; // error!
	FUNC_T f2 = outer<X>::template g<double>; // correct
}
int main(){
	do_it<int>();
	system("pause");
}
**/
/**
template <typename T>
T max1(const T& a, const T& b)
{
	return 1;
}
template <typename T>
int max2(const T& a, const T& b)
{
	return 0;
}
int main(){
	max2(3.0, 5.0);
	max1(3.0, 5.0);
	system("pause");
}**/
/**
class MyClass
{
private:
	double x_;
	int z_;
public:
	template <typename stream_t>
	void write_x_to(stream_t& y){
		
	}
};
struct MyClassHACK
{ };
template <>
void MyClass::write_x_to(MyClassHACK&)
{

}
**/
/**
///////////// WAZNE !!!!!!!!!!! WAZNE!!!!!!!!!!!////////////////////
struct var { static const int value = 5; };
struct type { typedef int types; };

template<typename T>
void funvar(){
	typename T::types i = 10;
	cout << i;
}

template<typename T>
void fun(){
	cout << typename T::value;
}

int main(){
	funvar<type>();
	fun<var>();
	system("pause");
}////////////////////////////////////////////////////////
**/

///https://www.youtube.com/watch?v=dyHWVQE3Oo4 15:20 min 

/**
//MIXINS
template<typename T>
struct list{
	list() {
		next = Head();
		Head() = static_cast<const T*>(this);}

	const T* Next(void) const { return next; }

	static const T*& Head(void){
		static const T *p = 0;
		return p; }

private:
	const T* next;
};


struct mylist : list < mylist > {
	mylist(int j) : x(j) {}
	int x;
};
int main(){
	
	mylist s(1);
	mylist j(2);
	mylist ds(4);

	for (const mylist *i = mylist::Head(); i; i = i->Next())
	std::printf("%d", i->x);

	cout << endl;
	int a = 5;
	int *b;
	b = &a;
	cout << b << endl;
	cout << *b << endl;
	system("pause");
	
}

**/
/**
template <typename T>
struct outer
{
	template <int N>
	struct inner
	{
		friend void operator++(inner<N>)
		{
			inner* a = new inner();
		}
	};
};
int main(){
	outer<double>::inner<0> I1;
	++I1; // returns outer<double>::inner<1>
	system("pause");
}**/
/**
int f(double){

};
int main(){

	unique_ptr<int> a;
	auto p = make_shared < int >();
	*p = 5;
	shared_ptr<int> b;
	*b = 5;
	auto f(double)->int;
	auto i{ 42 };
	auto x = shared_ptr < int > {make_unique<double>()};
	bool px = is_same < int, int >() ;
}**/
/**
template <typename T>
struct X
{
	T member_;
	X(T value)
		: member_(value)
	{
	}
};
double f(int)
{
	return 3.14;
}
int main(){
//X<double(int)> t1(f); // error: cannot construct 'member_'
X<double(*)(int)> t2(f); // ok: 'member_' is a pointer
cout << t2.member_;
system("pause");
}**/
/**
template <typename scalar_t>
inline scalar_t sq(const scalar_t& x); // (1) function template

template <>
inline double sq(const double& x){
	cout << "specjalizaion"<<endl;
	return x * 2;
};

inline double sq(const double& x){
	cout << "overload" << endl;
	return x * 1;
}; // (2) overload

int main(){

	auto a = sq<double>(3.14);
	cout << a;
	system("pause");
}**/
/**
class debugs{
private:
	int b;
public:
	int a;
	void operator()(const char *&a){
		cout << a;
	}
	debugs& operator++(){
		auto as = "x";
		debugs *a = new debugs();
		a->operator()(as);
		*this = *a;
		return *this;
	}
	debugs& operator+(const debugs my){
		debugs* super = new debugs();
		super->a = a + my.a;
		return *super;
	}
	template<typename T>
	T newes(){
		return static_cast<T>(*this);
	}

};

int main(){

	auto as = "a";
	debugs a1;
	a1(as);
	a1++;
	a1.a = 4;
	debugs a2;
	a2.a = 5;
	unique_ptr<debugs> nowe(new debugs);
	*nowe = a1 + a2;
	cout << nowe->a;

	int b[10];
	for (auto &c : b){
		c = 10;
		cout << c;
	}

	system("pause");
}
**/
/**
template<typename T>
class Weapon{
public:
	Weapon(){}
private:
	T sword;
};
template<typename T>
class Armor{
public:
	Armor(){}
private:
	T armor;
};
template<typename T>
class Hero{
public:
	Hero(string name) : name(name) {
		Weapon<T> start_weapon;
		Armor<T> start_armor;
		hp = 200;
		mana = 100;
		level = 0;
	}

private:
	string name;
	int hp;
	int mana;
	int level;

};

int main(){

	Hero<string> myhero("Patryk");


	auto gamerunning=true;
	while (gamerunning){





		system("cls");
	}
	return 0;
}**/
/**
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock

std::mutex mtx;           // mutex for critical section

void print_block(int n, char c) {
	// critical section (exclusive access to std::cout signaled by lifetime of lck):
	std::unique_lock<std::mutex> lck(mtx);
	for (int i = 0; i<n; ++i) { std::cout << c; }
	std::cout << '\n';
}

int main()
{
	std::thread th1(print_block, 150, '*');
	std::thread th2(print_block, 50, '$');

	th1.join();
	th2.join();

	system("pause");
}
**/
/**
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;
class position{
public:
	int x;
	int y;
};

class gamemap:public position{
public:
	gamemap(int _width, int _lenght);
	void printmap(position *pos);
	bool operator()();
	friend class hero;
private:
	char **size;
	int lenght;
	int width;
	bool gamestatus;

};
gamemap::gamemap(int _width, int _lenght) : width(_width), lenght(_lenght) {
	size = new char *[lenght];
	for (int i = 0; i < lenght; i++){
		size[i] = new char[width];
	}
};
void gamemap::printmap(position *pos){
	for (int i = 0; i < lenght; i++){
		for (int j = 0; j < width; j++){
			if (i == 0 || i == lenght-1 || j ==0 || j == width-1){
				size[i][j] = 'X';
			}
			else{
				size[i][j] = ' ';
			}

		}
	}

	for (int i = 0; i < 4; i++){
	size[pos[i].x][pos[i].y] = '*';
	}


	for (int i = 0; i < lenght; i++){
		for (int j = 0; j < width; j++){
			cout << size[i][j];
		}
		cout << endl;
	}

}
bool gamemap::operator()(){
	return gamestatus = true;
}


class hero{
public:
	hero();
	position *getposition();
	void moving(gamemap &friends);
private:
	
	position *pos;
	const int sizes = 4;

};
hero::hero(){
	pos = new position[sizes];
	for (int i = 0; i < sizes; i++)
	{
		pos[i].x = i + 0;
		pos[i].y = i + 3;
	}
}
position *hero::getposition(){
	return pos;
}
void hero::moving(gamemap &friends){
	if ((friends.size[pos[0].x + 1][pos[0].y] != 'X') && (friends.size[pos[1].x + 1][pos[1].y] != 'X') && (friends.size[pos[2].x + 1][pos[2].y] != 'X') && (friends.size[pos[3].x + 1][pos[3].y] != 'X')){
		for (int i = 0; i < sizes; i++){
			Sleep(200);
			pos[i].x++;
		}
	}
	if (_kbhit()){
			switch (_getch())
			{
			case 'd':
				if ((friends.size[pos[0].x][pos[0].y + 1] != 'X') && (friends.size[pos[1].x][pos[1].y + 1] != 'X') && (friends.size[pos[2].x][pos[2].y + 1] != 'X') && (friends.size[pos[3].x][pos[3].y + 1] != 'X') ){
					for (int i = 0; i < sizes; i++){
						pos[i].y++;
					}
				}
				break;
			case 'a':
				if ((friends.size[pos[0].x][pos[0].y - 1] != 'X') && (friends.size[pos[1].x][pos[1].y - 1] != 'X') && (friends.size[pos[2].x][pos[2].y - 1] != 'X') && (friends.size[pos[3].x][pos[3].y - 1] != 'X')){
					for (int i = 0; i < sizes; i++){
						pos[i].y--;
					}
				}
				break;
			}
		}
}

int main()
{

	gamemap nowamapa(20,20);
	hero bohater;

	while (nowamapa()){

		bohater.moving(nowamapa);
		nowamapa.printmap(bohater.getposition());
		cout << endl;
		cout << "      Tetris";
		system("cls");
	}

	
	system("pause");
}**/
/**
class shape{
public:
	shape(){};
	virtual void printsth(){}
};

class square: public shape{
public:
	square(){}
	void printsth(){
		cout << "2. Square Class";
	}
};


class A { public: void Foo() {} 
int m;
};
class B : public virtual A {};
class C : public virtual A {};
class D : public B, public C {};

int main(){
	shape *shap;
	square a;
	shap = &a;
	shap->printsth();

	vector<int> as(5);

	D d;
	d.Foo();
	d.B::m = 6;
	d.C::m = 5;
	cout << d.m;
	system("pause");
}**/
/**
enum A{FIRST,SECOND};
void print(int a){
	switch (a){
	case FIRST:
		cout << "First";
			break;
	case SECOND:
		cout << "Second";
		break;
	}

}
void setvalue(istream& is, double &a) 
{
	is >> a;
}
void printvalue(ostream& is, double &a) 
{
	is << a;
	is.imbue(locale{ "en_US.UTF-8" });
}
int main(){
	int a = A::SECOND;
	print(a);
	double myval = 0;
	setvalue(std::cin, myval);
	printvalue(std::cout, myval);
	system("pause");
}**/
/**
#include <iterator>
#include<assert.h>

template<typename Iter>
void advance(Iter p, int n) 
{
	advance_helper(p, n, typename iterator_traits<Iter>::value_type{});
}
template<typename Iter>
void advance_helper(Iter p, int n, random_access_iterator_tag)
{
	p += n;
}

int main(){
	int a[4] = { 0, 1, 2, 3 };

	advance(a, 2);
	assert(a == NULL);

	system("pause");
}**/
/**
class pointer{
public:
	pointer *next;
	int data;
};

void push_pointer(pointer *&p, int data){
	pointer *newptr = new pointer;
	newptr->next = p;
	newptr->data = data;
	p = newptr;
}

void print(pointer *&p){
	while (p != NULL && p->next != NULL)
	{

		cout << " " << p->data;
		p = p->next->next;
	}
}
int main()
{
	pointer *my;
	push_pointer(my, 5);
	push_pointer(my, 9);
	push_pointer(my, 9);
	print(my);
	system("pause");
}**/
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <csignal>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

template< class it >
void functions(it i1, it i2)
{
	iterator_traits<it>::iterator_category cat;
	iterator_traits<it>::difference_type n = std::distance(i1, i2);
	cout << n << endl;
	cout << typeid(cat).name() << endl;
	while (i1 != i2)
	{
		iterator_traits<it>::value_type x;
		x = *i1;
		cout << x << " ";
		i1++;
	};
	cout << endl;
};

int main()
{
	_CrtMemState s1,s2,s3;

	_CrtMemCheckpoint(&s1);
	vector<char> vc(10, 'a');
	functions(vc.begin(), vc.end());
	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
	system("pause");
}
