#include "Factory.h"

int main() {
	std::cout << "Programm for Kostov's special course by Fedin Nikita NSU MMF 13121" << std::endl;


	srand((unsigned int)time(NULL));

	int CountFigure;
	std::cin >> CountFigure;

	//чтобы после запятой выводилась только одна цифра
	std::cout << std::fixed;
	std::cout.precision(1);

	Container <Shape *> FigureList;
	for (int i = 0; i < CountFigure; ++i) {
		try {
			Shape * s = CreateFigure(rand() % 6);
			FigureList.AddEnd(s);
		}
		catch (DegenerateFigureException ex) {
			--i;
			ex.what();
		}
	}

	std::cout << "Count of shapes: " << Shape::CountShapes << std::endl;
	
	for (int i = 0; i < CountFigure; ++i) {
		std::cout << FigureList[i]->GetString() << " ";
		FigureList[i]->PrintInfo();
		std::cout << std::endl;
	}
	
	for (int i = 0; i < CountFigure; ++i) {
		delete FigureList[i];
	}
	FigureList.Clear();

	std::cout << "Count of shapes: " << Shape::CountShapes << std::endl;

	


	system("pause");
	return 0;
}