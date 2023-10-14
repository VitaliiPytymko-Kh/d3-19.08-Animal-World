#include <iostream>

using namespace std;
//абстрактный продукт1
class Herbivore 
{
public:
    int Weight;
    bool Life;
    virtual void EatGrass() = 0;
    virtual bool IsAlive() = 0;
    Herbivore() : Weight(0), Life(true) {}
};
//конкретный продукт абстрактного продукта1
class Wildebeest : public Herbivore
{
public:
    Wildebeest() : Herbivore() { Weight = 100; }
    void EatGrass() override
    {
        if (Life)
        {
            Weight += 10;
            cout << "Анттилопа наелась, новый вес : " << Weight << endl;
        }
    }

    bool IsAlive() override
    {
        return Life;
    }
};
//конкретный продукт абстрактного продукта1
class Bison : public Herbivore {
public:
    Bison() :Herbivore() { Weight = 350; }
    void EatGrass()override {
        if (Life) {
            Weight += 10;
            cout << "Биз0н поел, новый вес:" << Weight << endl;
        }
    }
    bool IsAlive() override
    {
        return Life;
    }
};
//конкретный продукт абстрактного продукта1
class Elk : public Herbivore {
public: 
    Elk() :Herbivore() { Weight = 200; }
    void EatGrass()override {
        if (Life) {
            Weight += 10;
            cout << "ЛОсь поел, Новый вес :" << Weight << endl;
        }
    }
    bool IsAlive() override
    {
        return Life;
    }
};
//абстрактный продукт2
class Carnivore //абстрактный продукт2
{
public:
    int Power;
    Carnivore() : Power(0) {}
    virtual void Eat(Herbivore* herbivore) = 0;
};
//конкретный продукт абстрактного продукта2
class Lion : public Carnivore
{
public:
    Lion() : Carnivore() { Power = 250; }
    void Eat(Herbivore* herbivore) override
    {
        if ((Power*2) >= herbivore->Weight)
        {
            Power += 10;
            herbivore->Life = false;
            cout << "Лев сьел антилопу. Сила льва: " << Power << endl;
            cout << "жизнь антилопы: " << herbivore->Life << endl;
        }
        else
        {
            Power -= 10;
            cout << "леа не смогг победить антилопу. сила Льва: " << Power << endl;
        }
    }
};
//конкретный продукт абстрактного продукта2
class Wolf :public Carnivore {
public: Wolf() : Carnivore() { Power = 100; }
      void Eat(Herbivore* herbivore) override {
          if ((Power * 2) >= herbivore->Weight) {

              Power += 10;
              herbivore->Life = false;
              cout << "волки съел Бизона. Сила волка:" << Power << endl;
              cout << "бизон жив:" << herbivore->Life << endl;
          }
          else {
              Power -= 10;
              cout << "Сила волка :" << Power << endl;
          }
      }
};
//конкретный продукт абстрактного продукта2
class Tiger :public Carnivore
{
public:
    Tiger() :Carnivore() { Power = 200; };
    void Eat(Herbivore* herbivore)override {
        if ((Power * 2) >= herbivore->Weight) {

            Power += 10;
            herbivore->Life = false;
            cout << "Тигр съел Лося. Сила Тигра:" << Power << endl;
            cout << "Лось живой:" << herbivore->Life << endl;
        }
        else {
            Power -= 10;
            cout << "Сила тигра:" << Power << endl;
        }
    }
};
//абстрактная фабрика
class IContinent
{
public:
    virtual Herbivore* CreateHerbivore() = 0;
    virtual Carnivore* CreateCarnivore() = 0;
};
//конкректная фабрика
class Africa : public IContinent
{
public:
    Herbivore* CreateHerbivore() override
    {
        cout << "Антилопа Создана." << endl;
        return new Wildebeest();
    }

    Carnivore* CreateCarnivore() override
    {
        cout << "Лев создан." << endl;
        return new Lion();
    }
};
//конкректная фабрика
class NorthAmerica :public IContinent {
public:
    Herbivore* CreateHerbivore() override {
        cout << "Бизон создан" << endl;
        return new Bison();
    }
    Carnivore* CreateCarnivore()override {
        cout<<"Волк создан" << endl;
        return new Wolf();
    }
};
//конкректная фабрика
class Eurasia : public IContinent {
public :
    Herbivore* CreateHerbivore()override {
        cout << "Лось создан" << endl;
        return new Elk();
    }
    Carnivore* CreateCarnivore()override {
        cout << "Тигр создан" << endl;
        return new Tiger();
    }
};
//клиент
class AnimalWorld
{
public:
    void MealsHerbivores(Herbivore** herbivores, int count)
    {
        cout << "всех травоядных приступить к кормежке:" << endl;
        for (int i = 0; i < count; i++) {
            herbivores[i]->EatGrass();
        }
        cout << "Травоядных животных покормили." << endl;
    }

    void NutritionCarnivores(Carnivore** carnivores, int count, Herbivore** herbivores, int herbivoreCount)
    {
        cout << "всех плотоядных охотится на травоядных:" << endl;
        for (int i = 0; i < count; i++) {
            int targetIndex = rand() % herbivoreCount; 
            Herbivore* targetHerbivore = herbivores[targetIndex]; 
            carnivores[i]->Eat(targetHerbivore); 
        }
        cout << "Охота хищников окончена ." << endl;
    }
};
//функция для создания масивов животных
void CreateAnimals(IContinent* continent, Herbivore** herbivores, Carnivore** carnivores, int herbivoreCount, int carnivoreCount)
{
    for (int i = 0; i < herbivoreCount; i++) {
        herbivores[i] = continent->CreateHerbivore();
    }
    for (int i = 0; i < carnivoreCount; i++) {
        carnivores[i] = continent->CreateCarnivore();
    }
}


  int main()
  {
      setlocale(LC_ALL,"");
      IContinent* africa = new Africa();
      IContinent* northAmerica = new NorthAmerica();
      IContinent* eurasia = new Eurasia();

      // Создаем массивы животных для каждого континента
      Herbivore* herbivoresAfrica[3];
      Carnivore* carnivoresAfrica[2];
      CreateAnimals(africa, herbivoresAfrica, carnivoresAfrica, 3, 2);

      Herbivore* herbivoresNorthAmerica[5];
      Carnivore* carnivoresNorthAmerica[3];
      CreateAnimals(northAmerica, herbivoresNorthAmerica, carnivoresNorthAmerica, 5, 3);

      Herbivore* herbivoresEurasia[10];
      Carnivore* carnivoresEurasia[5];
      CreateAnimals(eurasia, herbivoresEurasia, carnivoresEurasia, 10, 5);

      AnimalWorld world;

      // Кормим животных
      world.MealsHerbivores(herbivoresAfrica, 3);
      world.NutritionCarnivores(carnivoresAfrica, 2, herbivoresAfrica, 3);

      world.MealsHerbivores(herbivoresNorthAmerica, 5);
      world.NutritionCarnivores(carnivoresNorthAmerica, 3, herbivoresNorthAmerica, 5);

      world.MealsHerbivores(herbivoresEurasia, 10);
      world.NutritionCarnivores(carnivoresEurasia, 5, herbivoresEurasia, 10);
  return 0;

      
  }
       