// TransportConApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

enum TransportTypes
{
	TP_MOTORBIKE = 0,
	TP_SCOOTER = 1,
	TP_CAR = 2,
	TP_BUS = 3,
};

// Base transport class.
class CBaseTransport
{
public:
	CBaseTransport(std::wstring namestr, int wheels, int speed) : name(namestr)
		, max_wheels(wheels), max_speed(speed)
	{
	}
	virtual ~CBaseTransport() = default;

	virtual void PrintParams() const
	{
		std::wcout << L"Наименование транспорта: " << GetName() << std::endl;
		std::wcout << L"Кол-во колёс: " << GetMaxWheels() << std::endl;
		std::wcout << L"Максимальная скорость: " << GetMaxSpeed() << std::endl;
		std::wcout << std::endl;
	}

	inline std::wstring_view GetName() const { return name; }
	inline int GetMaxWheels() const { return max_wheels; }
	inline int GetMaxSpeed() const { return max_speed; }

private:
	std::wstring name;
	int max_wheels, max_speed;
};

class CMotorbike : public CBaseTransport
{
public:
	CMotorbike() : CBaseTransport(L"Мотоцикл", 2, 350)
	{
	}
};

class CScooter : public CBaseTransport
{
public:
	CScooter() : CBaseTransport(L"Скутер", 2, 25)
	{
	}
};

class CCar : public CBaseTransport
{
public:
	CCar() : CBaseTransport(L"Автомобиль", 4, 150)
	{
	}
};

class CBus : public CBaseTransport
{
public:
	CBus() : CBaseTransport(L"Автобус", 6, 100), max_passengers(20)
	{
	}

	void PrintParams() const override
	{
		std::wcout << L"Наименование транспорта: " << GetName() << std::endl;
		std::wcout << L"Кол-во колёс: " << GetMaxWheels() << std::endl;
		std::wcout << L"Максимальная скорость: " << GetMaxSpeed() << std::endl;
		std::wcout << L"Максимальное количество пассажиров: " << GetMaxPassengers() << std::endl;
		std::wcout << std::endl;
	}

	inline int GetMaxPassengers() const { return max_passengers; }

private:
	int max_passengers;
};

class CTransportFactory
{
public:
	static std::unique_ptr<CBaseTransport> createTransport(int type)
	{
		switch (type)
		{
		case TP_MOTORBIKE: return std::make_unique<CMotorbike>();
		case TP_SCOOTER: return std::make_unique<CScooter>();
		case TP_CAR: return std::make_unique<CCar>();
		case TP_BUS: return std::make_unique<CBus>();
		default: return nullptr;
		}
	}
};

int main(int argc, char* argv[])
{
#if defined(_WIN32) || defined(_WIN64)
	setlocale(LC_ALL, "Russian");
#else
	setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

	if (argc < 2)
	{
		std::wcout << L"Не указан тип транспорта." << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++)
	{
		// Convert the string value to an integer.
		int type = std::atoi(argv[i]);

		auto transport = CTransportFactory::createTransport(type);
		if (transport == nullptr)
		{
			std::wcout << L"НЕИЗВЕСТНЫЙ ТИП ТРАНСПОРТА" << std::endl;
			continue;
		}

		transport->PrintParams();
	}

	return 0;
}