#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

//Группа 1 номер 0
stats bubble_sort(vector<int>& numbers)
{
	stats stat_this_sort;
	int i = 1, j = 1;
	while (i < numbers.size())
	{
		if (i != 0 && numbers[i] < numbers[i - 1])
		{
			stat_this_sort.comparison_count++;
			j = i;
			while (j != 0 && numbers[j] < numbers[j - 1])
			{
				stat_this_sort.comparison_count++;
				stat_this_sort.copy_count+=3;
				swap(numbers[j], numbers[j - 1]);
				j--;
			}
			i = j;
		}
		else
			i++;
	}
	return stat_this_sort;
}
//Группа 2 номер 2
stats comb_sort(vector<int>& numbers)
{
	stats stat_this_sort;
	int pace = numbers.size() / 1.247;
	while (pace > 0)
	{
		int i = pace;
		while (i < numbers.size())
		{
			stat_this_sort.comparison_count++;
			if (numbers[i - pace] > numbers[i])
			{
				stat_this_sort.copy_count+=3;
				swap(numbers[i - pace], numbers[i]);
			}
			i++;
		}
		pace = pace / 1.247;
	}
	return stat_this_sort;
}
//Группа 3 номер 2
stats pyramid_sort(vector<int>& numbers)
{
	stats stat_this_sort;
	vector<int> temp;
	int size = numbers.size();
	for(size_t i = 0; i < size; i++)
	{
		int l_r = numbers.size() / 2 - (1 + (numbers.size() / 2 - int(numbers.size() / 2)));
		for (int j = l_r; j >= 0; j--)
		{
			if (2 * j + 2 < numbers.size())
			{
				stat_this_sort.comparison_count++;
				if (numbers[j] < numbers[2 * j + 2] && numbers[2 * j + 1] <= numbers[2 * j + 2])
				{
					stat_this_sort.copy_count+=3;
					swap(numbers[j], numbers[2 * j + 2]);
				}
				else if (numbers[j] < numbers[2 * j + 1] && numbers[2 * j + 2] <= numbers[2 * j + 1])
				{
					stat_this_sort.copy_count += 3;
					swap(numbers[j], numbers[2 * j + 1]);
				}
			}
			else
			{
				stat_this_sort.comparison_count++;
				if (numbers[j] < numbers[2 * j + 1])
				{
					stat_this_sort.copy_count += 3;
					swap(numbers[j], numbers[2 * j + 1]);
				}
			}
		}
		stat_this_sort.copy_count += 3;
		swap(numbers[0], numbers[numbers.size() - 1]);
		temp.insert(temp.begin(), numbers[numbers.size() - 1]);
		numbers.pop_back();
	}
	numbers = temp;
	return stat_this_sort;
}

ostream& operator<<(ostream& out, const vector<int>& numbers)
{
	out << "{";
	for (size_t i = 0; i < numbers.size(); i++)
	{
		out << numbers[i];
		if (i + 1 < numbers.size())
			out << ", ";
	}
	out << "}";
	return out;
}

void write_file_data(int* n, int size, int seed, string filename)
{
	//Для проверки создаём только один файл
	for (int I = 0; I < 1; I++)
	{
		string Filename = filename + char(49+I) + ".txt";
		ofstream my_data;
		my_data.open(Filename);
		my_data << n[I] << ":  \n\n";
		my_data << "Bubble:           " << "Comb:            " << "Pyramid:" << "\n\n";
		srand(seed);
		vector<int>* array_arrays1 = new vector<int>[100];
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < n[I]; j++)
				array_arrays1[i].insert(array_arrays1[i].begin(), rand());
		}
		vector<int>* array_arrays2 = new vector<int>[100];
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < n[I]; j++)
				array_arrays2[i].insert(array_arrays2[i].begin(), array_arrays1[i][n[I] - 1 - j]);
		}
		vector<int>* array_arrays3 = new vector<int>[100];
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < n[I]; j++)
				array_arrays3[i].insert(array_arrays3[i].begin(), array_arrays1[i][n[I] - 1 - j]);
		}
		//Для проверки сделал
		cout << array_arrays1[0] << endl << endl;
		cout << array_arrays1[1] << endl << endl;
		cout << array_arrays2[0] << endl << endl;
		cout << array_arrays2[1] << endl << endl;
		cout << array_arrays3[0] << endl << endl;
		cout << array_arrays3[1] << endl << endl;
		for (int q = 0; q < 100; q++)
		{
			my_data << q+1 << ":  \n";
			stats B_srt = bubble_sort(array_arrays1[q]);
			stats C_srt = comb_sort(array_arrays2[q]);
			stats P_srt = pyramid_sort(array_arrays3[q]);
			my_data << "comp_cnt: " << B_srt.comparison_count << "  " << "comp_cnt: " << C_srt.comparison_count << "  " << "comp_cnt: " << P_srt.comparison_count << "  \n";
			my_data << "copy_cnt: " << B_srt.copy_count << "  " << "copy_cnt: " << C_srt.copy_count << "  " << "copy_cnt: " << P_srt.copy_count << "  \n\n";
		}
		//Для проверки сделал
		cout << array_arrays1[0] << endl << endl;
		cout << array_arrays1[1] << endl << endl;
		cout << array_arrays2[0] << endl << endl;
		cout << array_arrays2[1] << endl << endl;
		cout << array_arrays3[0] << endl << endl;
		cout << array_arrays3[1] << endl << endl;
		my_data.close();
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int n[]{1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000};
	int seed = 0;
	cout << "Введите зерно: ";
	cin >> seed;
	vector<int>* array_arrays1 = new vector<int>[100];
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 1000; j++)
			array_arrays1[i].insert(array_arrays1[i].begin(), rand());
	}
	for (int q = 0; q < 100; q++)
	{
		stats B_srt = comb_sort(array_arrays1[q]);
		cout << endl;
		cout << "comp_cnt: " << B_srt.comparison_count << endl;
		cout << "copy_cnt: " << B_srt.copy_count << endl;
	}
	write_file_data(n, 13, seed, "D:/Games/");//здесь указывается именно путь с последним элементо '/' далее название файла с расширение вводится функцией
	//vector<int> numbers{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	////Группа 1 номер 0
	//cout << "Bubble sort:" << endl;
	//cout << "До: " << numbers << endl;
	//stats bubble_res = bubble_sort(numbers);
	//cout << "comparison_count = " << bubble_res.comparison_count << endl;
	//cout << "copy_count = " << bubble_res.copy_count << endl;
	//cout << "После: " << numbers << endl;
	//numbers = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	////Группа 2 номер 2
	//cout << "Comb sort:" << endl;
	//cout << "До: " << numbers << endl;
	//stats comb_res = comb_sort(numbers);
	//cout << "comparison_count = " << comb_res.comparison_count << endl;
	//cout << "copy_count = " << comb_res.copy_count << endl;
	//cout << "После: " << numbers << endl;
	//numbers = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	////Группа 3 номер 2
	//cout << "Pyramid sort:" << endl;
	//cout << "До: " << numbers << endl;
	//stats pyramid_res = pyramid_sort(numbers);
	//cout << "comparison_count = " << pyramid_res.comparison_count << endl;
	//cout << "copy_count = " << pyramid_res.copy_count << endl;
	//cout << "После: " << numbers << endl;
}