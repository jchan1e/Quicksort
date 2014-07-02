// quicksort.cxx
//
// Jordan Dick
// jchan1e@gmail.com
//
// animates the quicksort algorithm and others
//
// Compile with the following command:
// g++ -Wall -lsfml-graphics -lsfml-window -lsfml-system  -g -o "quicksort" "quicksort.cxx"

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <SFML/graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

const int W = 1670;	// window width
const int S = 1000;	// window height
const int Q = 2;	// bar width
const int N = W/Q;	// array size
const int MAX = S;	// max possible value in the array

void quicksort(int arr[], int left, int right);
void draw_array(int n, int arr[], int max);
void lines(int i, int j);
int pixel(double wx, double w0, double w1, int p0, int p1);
void mergesort(int arr[], int lo, int hi);
void heapsort(int arr[], int lo, int hi);
void shift(int arr[], int lo, int hi);
void heapify(int arr[], int lo, int hi);
void swap(int arr[], int a, int b);
int parent(int child);
int left_child(int parent);
int right_child(int parent);
void heapsort2(int arr[], int lo, int hi);
void shift2(int arr[], int lo, int mid, int hi);
void heapify2(int arr[], int lo, int hi);
void swap2(int arr[], int a, int b);
int parent2(int child, int hi);
int left_child2(int parent2, int hi);
int right_child2(int parent2, int hi);

sf::RenderWindow window(sf::VideoMode(W, S), "Quicksort");

int main()
{
	//window = sf::RenderWindow(sf::VideoMode(W, S+5), "Quicksort");
	
	srand(time(NULL));

	window.setFramerateLimit(300);

	int array[N];
	int i;
	int temp, n;

//	srand(time(NULL));


// randomized array
	for(i = 0; i < N; ++i)
		array[i] = pixel(i, 0, N, 0, MAX);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

while(true)
{
	i = rand()%12;

	if (i == 0 || i == 1 || i == 11)
	{
		window.setFramerateLimit(120);
		for(i = 0; i < N; ++i)
		{
			temp = array[i];
			n = rand() %N;
			array[i] = array[n];
			array[n] = temp;

			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		} 

		quicksort(array, 0, N-1);
	}

// triangular arrays
	else if (i == 2)
	{
		window.setFramerateLimit(120);
		for(i = 0; i < N/2; ++i)
		{
			array[i] = pixel(i, 0, N/2, 0, MAX);
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		}
		for(i = N/2; i < N; ++i)
		{
			array[i] = pixel(i, N/2, N, MAX, 0)+1;
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		} 

		quicksort(array, 0, N-1);
	}
	else if (i == 3)
	{
		window.setFramerateLimit(120);
		for(i = 0; i < N/2; ++i)
		{
			array[i] = pixel(i, 0, N/2, MAX, 0);
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		}
		for(i = N/2; i < N; ++i)
		{
			array[i] = pixel(i, N/2, N, 0, MAX)+1;
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		} 

		quicksort(array, 0, N-1);
	}

// randomized array
	else if (i == 4)
	{
		window.setFramerateLimit(240);
		for(i = 0; i < N; ++i)
		{
			temp = array[i];
			n = rand() %N;
			array[i] = array[n];
			array[n] = temp;

			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		} 

		mergesort(array, 0, N-1); 
	}

// reversed array
	else if (i == 5)
	{
		window.setFramerateLimit(240)
	;	for(i = 0; i < N; ++i)
		{
			array[i] = pixel(i, 0, N, MAX, 0);
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		}

		mergesort(array, 0, N-1);
	}

// randomized array
	else if (i == 6 || i == 7)
	{
		window.setFramerateLimit(180);
		for(i = 0; i < N; ++i)
		{
			temp = array[i];
			n = rand() %N;
			array[i] = array[n];
			array[n] = temp;

			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		}

		heapsort(array, 0, N-1);
	}

// reverse sorted array
	else if (i == 8)
	{
		window.setFramerateLimit(240);
		for(i = 0; i < N; ++i)
		{
			array[i] = pixel(i, 0, N, MAX, 0);
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		}

		heapsort(array, 0, N-1);
	}

// triangular array
	else if (i == 9)
	{
		window.setFramerateLimit(240);
		for(i = 0; i < N/2; ++i)
		{
			array[i] = pixel(i, N/2, 0, MAX, 0);
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		}
		for(i = N/2; i < N; ++i)
		{
			array[i] = pixel(i, N, N/2, 0, MAX)+1;
			window.clear(sf::Color::Black);
			draw_array(N, array, MAX);
			window.display();
		}

		heapsort(array, 0, N-1);
	}

// sorted array
	else if (i == 10)
	{
		window.setFramerateLimit(240);
		heapsort(array, 0, N-1);
	}

}

// BOGO sort!
/*	for(i = 0; i < N; ++i)
	{
		array[i] = pixel(i, 0, N, MAX, 0);
		window.clear(sf::Color::Black);
		draw_array(N, array, MAX);
		window.display();
	}

	window.setFramerateLimit(0);
;
	bool sorted = false;
	for (int i = 0; array[i] < array[i+1] && i < N-1; ++i)
		{
			if (i == N-2)
				sorted = true;
		}
	while (!sorted && window.isOpen())
	{
		swap(array, rand() %N, rand() %N);
		window.clear();
		draw_array(N, array, MAX);
		window.display();
		// check all the window's events that were 
		// triggered since the last iteration of the loop
		for (int i = 0; array[i] < array[i+1] && i < N-1; ++i)
		{
			if (i == N-2)
				sorted = true;
		}

		sf::Event event;
		if (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	while (window.isOpen())
	{
		// check all the window's events that were 
		// triggered since the last iteration of the loop
		sf::Event event;
		if (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}*/

	return EXIT_SUCCESS;
}

void quicksort(int arr[], int left, int right)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed) {
			window.close();
			exit(0);
		}
	}

	int i = left, j = right;
	int tmp1 = arr[left], tmp2 = arr[(left+right)/2], tmp3 = arr[right];
	int pivot;
	if (tmp1 <= tmp2 && tmp2 < tmp3)
		pivot = tmp2;
	else if (tmp1 <= tmp3 && tmp3 < tmp2)
		pivot = tmp3;
	else
		pivot = tmp1;
	
	// partition
	while (i < j)
	{
		while (arr[i] < pivot)
			++i;
		while (arr[j] > pivot)
			--j;

	// draw
		window.clear(sf::Color::Black);
		draw_array(N, arr, MAX);
		lines(i, j);
		window.display();

//		swap
		if (i <= j)
		{
			swap(arr, i, j);
			++i;
			--j;
		}
	}
	
	// recursion
	/*if (rand() %2 == 1)
	{
		if (left < j)
			quicksort(arr, left, j);
		if (i < right)
			quicksort(arr, i, right);
	}
	else
	{*/
		if (i < right)
			quicksort(arr, i, right);
		if (left < j)
			quicksort(arr, left, j);
	//}
}

void mergesort(int arr[], int lo, int hi)
{

	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed) {
			window.close();
			exit(0);
		}
	}

	//recursion
	if (hi-lo > 1)
	{
		mergesort(arr, lo, hi-(hi-lo+1)/2);
		mergesort(arr, hi-(hi-lo+1)/2+1, hi);
	}

	if (hi != lo)
	{
		//split
		int range = hi-lo+1;
		int bsize = range/2;
		int asize = range-bsize;
		int arc[range];
		int arb[bsize];
		int ara[asize];

		int i = 0;

		for(i = 0; i < asize; ++i)
			ara[i] = arr[lo+i];
		
		for(i = 0; i < bsize; ++i)
			arb[i] = arr[lo+asize+i];

		int a = 0;
		int b = 0;
		int c = 0;


		//merge
		while (a < asize && b < bsize && c < range)
		{
			window.clear();
			draw_array(N, arr, MAX);
			lines(lo + a, lo + asize + b);
			window.display();

			if (ara[a] <= arb[b])
			{
				arc[c] = ara[a];
				++a;
				++c;
			}

			else
			{
				arc[c] = arb[b];
				++b;
				++c;
			}
		}

		while (a < asize && c < range)
		{
			arc[c] = ara[a];
			++a;
			++c;
			window.clear();
			draw_array(N, arr, MAX);
			lines(lo + a, lo + asize + b);
			window.display();
		}

		while (b < bsize && c < range)
		{
			arc[c] = arb[b];
			++b;
			++c;
			window.clear();
			draw_array(N, arr, MAX);
			lines(lo + a, lo + asize + b);
			window.display();
		}

		for(i = 0; i < range; ++i)
		{
			arr[lo + i] = arc[i];
		}

		window.clear();
		draw_array(N, arr, MAX);
		window.display();
	}

}

void heapsort(int arr[], int lo, int hi)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed) {
			window.close();
			exit(0);
		}
	}

	heapify(arr, lo, hi);
	for(int i = hi; i > 0; --i)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				window.close();
				exit(0);
			}
		}

		shift(arr, lo, i);
		swap(arr, 0, i);
		window.clear();
		draw_array(N, arr, MAX);
		window.display();
	}
}

void shift(int arr[], int lo, int hi)
{
	int a = lo;
	int b = a;
	while (left_child(a) <= hi)
	{
		if (arr[b] < arr[left_child(a)])
			b = left_child(a);
		if (right_child(a) <= hi && arr[b] < arr[right_child(a)])
			b = right_child(a);
		if (b != a)
		{
			swap(arr, a, b);
			a = b;
		}
		else
			break;
		window.clear();
		draw_array(N, arr, MAX);
		window.display();
	}
	return;
}

void heapify(int arr[], int lo, int hi)
{
	for(int mid = (hi-lo-1)/2; mid >= 0; --mid)
	{
		shift(arr, mid, hi);
		window.clear();
		draw_array(N, arr, MAX);
		window.display();
	}
}

void swap(int arr[], int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void shift2(int arr[], int lo, int mid, int hi)
{
	int a = mid;
	int b = a;
	while (left_child2(a, hi) >= lo)
	{
		if (arr[a] < arr[left_child2(a, hi)])
			b = left_child2(a, hi);
		if (right_child2(a, hi) >= lo && arr[b] < arr[right_child2(a, hi)])
			b = right_child2(a, hi);
		if (b != a)
		{
			swap(arr, a, b);
			//lines(a, b);
			a = b;
			//window.clear();
			//draw_array(N, arr, MAX);
			//window.display();
		}
		else
			break;
	}
	//window.clear();
	//draw_array(N, arr, MAX);
	//window.display();
	return;
}

void heapify2(int arr[], int lo, int hi)
{
	for(int mid = (hi-lo)/2; mid <= hi; ++mid)
	{
		shift2(arr, lo, mid, hi);
		window.clear();
		draw_array(N, arr, MAX);
		window.display();
	}
}

void heapsort2(int arr[], int lo, int hi)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed) {
			window.close();
			exit(0);
		}
	}

	heapify2(arr, lo, hi);
	for(int i = hi; i > lo; --i)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				window.close();
				exit(0);
			}
		}

		heapify2(arr, lo, i);
		//shift2(arr, lo, i, i);
		//swap(arr, 0, i);
		//window.clear();
		//draw_array(N, arr, MAX);
		//window.display();
	}
}

int parent(int child) {return (child - 1)/2;}
int left_child(int parent) {return 2*parent + 1;}
int right_child(int parent) {return 2*parent + 2;}

int parent2(int child, int hi) {return child+1+(hi-child)/2;}
int left_child2(int parent2, int hi) {return hi-2*(hi-parent2) - 1;}
int right_child2(int parent2, int hi) {return hi-2*(hi-parent2) - 2;}

void draw_array(int n, int arr[], int max)
{
	int i; //y;

/*	sf::RectangleShape rectangle(sf::Vector2f(3,10));

	rectangle.setFillColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color::White);

	for(i = 0; i < n; ++i)
	{
		y = pixel(double(arr[i]), double(0), double(max), 0, S);	
		rectangle.setPosition(sf::Vector2f(5*i+1, S));
		rectangle.setSize(sf::Vector2f(1, -y));
		window.draw(rectangle);
	}
	*/

	sf::Vertex line0[] =
	{	sf::Vertex(sf::Vector2f(0, 0)),
		sf::Vertex(sf::Vector2f(0, 0)),
		/*sf::Vertex(sf::Vector2f(0, 0))*/  };


	for(i = 0; i < n; ++i)
	{
		line0[0] = sf::Vertex(sf::Vector2f(Q*i, S));
		line0[1] = sf::Vertex(sf::Vector2f(Q*i, S-arr[i]));
		//line0[2] = sf::Vertex(sf::Vector2f(Q*i, 0));
		line0[1].color = sf::Color::Color (
			min(abs(std::max(abs(((2*arr[i]+512) %1536)-768)-256,0)),255),
			min(abs(std::max(abs(((2*arr[i]) %1536)-768)-256,0)),255),
			min(abs(std::max(abs(((2*arr[i]-512) %1536)-768)-256,0)),255));
		line0[0].color = sf::Color::Black;
		//line0[2].color = line0[0].color;
		window.draw(line0, 2, sf::Lines);//Strip);
	}
}

void lines(int i, int j)
{
	sf::Vertex line1[] =
	{
		sf::Vertex(sf::Vector2f(Q*i, 0)),
		sf::Vertex(sf::Vector2f(Q*i, S))
	};
	line1[0].color = sf::Color::Red;
	line1[1].color = sf::Color::Red;


	sf::Vertex line2[] =
	{
		sf::Vertex(sf::Vector2f(Q*j, 0)),
		sf::Vertex(sf::Vector2f(Q*j, S))
	};
	line2[0].color = sf::Color::Green;
	line2[1].color = sf::Color::Green;

	window.draw(line1, 2, sf::Lines);
	window.draw(line2, 2, sf::Lines);
}

int pixel(double wx, double w0, double w1, int p0, int p1)
{
	double x = (wx-w0)/(w1-w0);
	int px = int (x*(p1-p0)+p0);
	return px;
}