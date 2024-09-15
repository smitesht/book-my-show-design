# The Movie Theater Seat Reservation System

## Overview

The Movie Theater Seat Reservation System is designed to efficiently manage the seating arrangements in a theater with various seat categories (like Gold, Silver, VIP), update seat prices dynamically, and allow users to reserve tickets. The system also handles multiple shows running in different screen halls.

## Key Features

- **Seat Management**: Supports multiple categories of seats like Gold, Silver, VIP, and Executive with dynamic prices.
- **Screen Hall Construction**: Multiple screen hall creation with Builder Design Pattern.
- **Show and Movie Management**: Each show is tied to a specific movie and screen hall, and the system can manage the scheduling and seating for each show.
- **Reservation and Ticketing**: Users can select available seats and book the seats. Able to display seat status in real-time seat layout on a console.
- **Payment Processing**: Supports multiple payment strategies like Credit Card, PayPal, and Stripe.
- **Code Extensibility**: The code is easy to scalable and extensible. Try to cover possible design principles and patterns.

## Key Design Patterns

- **Factory Pattern**: The SeatFactory class dynamically creates seat objects based on the seat type.
- **Builder Pattern**: The ScreenHallBuilder allows for the flexible creation of a screen hall by adding rows of seats.
- **Strategy Pattern**: The PaymentManager allows different payment strategies, allowing flexibility in payment processing methods.

## Code Walkthrough

- **Seat**: The Seat class manages seat properties like seat type, number, and reservation status.
- **ScreenHall**: Objects of the ScrenHall class are created using the ScreenHallBuilder. The class supports seating arrangements, price updation, helper method for seat reservation, seat cancellation, display seating arrangments, etc,
- **Show**: The Show class objects are created using ShowPlanner. The class uses ScreenHall, Movie, and ShowTime to manage the show. It also supports price updation based on seat categories, cancellation of shows, helper method for cancellation of seats, etc.
- **BookingManager**: The BookingManager selects the theater, show, and seats, and books the ticket after processing payment.

![image](https://github.com/user-attachments/assets/d7ff2785-c264-4e52-84b7-37dc66ec1e0c)

![Seat](https://github.com/user-attachments/assets/8df02b20-d18c-4ca6-8a01-f464cbd455e1)

## Code Snippets

```cpp

enum class SeatType
{
	Gold,
	Silver,
	Vip,
	Premium,
	Executive,
	Standard
};

enum class ReservationStatus {
	Empty,
	Selected,
	Reserved
};

enum class ShowStatus
{
	Running,
	Cancelled,
	CommingSoon
};

```

```cpp
class Seat
{
private:
	string seatID; // row + rowSeatID e.g. A21, B12
	string rowID; // A, B,...
	int rowSeatID; // 1, 2
	SeatType seatType;
	ReservationStatus reservationStatus;
	double price;
public:
	Seat(SeatType type, string rowid, int id)
		:seatType(type), rowID(rowid), rowSeatID(id),
		price(0), reservationStatus(ReservationStatus::Empty)
	{
		seatID = rowID + to_string(rowSeatID);
	}

	string getSeatId() { return seatID; }
	string getRowId() { return rowID; }
	int getRowSeatId() { return rowSeatID; }
	SeatType getSeatType() { return seatType; }
	ReservationStatus getReservationStatus() { return reservationStatus; }
	double getPrice() { return price; }

	void setPrice(double price) { this->price = price; }
	void setSeatReserved() { reservationStatus = ReservationStatus::Reserved; }
	void setSeatUnreserved() { reservationStatus = ReservationStatus::Empty; }
	void setSeatSelectedForBooking() { reservationStatus = ReservationStatus::Selected; }

	string getSeatTypeInString() {
		switch (seatType)
		{
		case SeatType::Gold:
			return "Gold";
			break;
		case SeatType::Silver:
			return "Silver";
			break;
		case SeatType::Vip:
			return "Vip";
			break;
		case SeatType::Premium:
			return "Premium";
			break;
		case SeatType::Executive:
			return "Executive";
			break;
		case SeatType::Standard:
			return "Standard";
			break;
		default:
			break;
		}
	}

	string getReservationStatusToString() {
		switch (reservationStatus)
		{
		case ReservationStatus::Empty:
			return " ";
			break;
		case ReservationStatus::Selected:
			return "S";
			break;
		case ReservationStatus::Reserved:
			return "R";
			break;
		default:
			break;
		}
	}

};

```

```cpp

class SeatFactory
{
public:
	vector<shared_ptr<Seat>> CreateSeats(SeatType seatType, string rowId, int startSeatId, int endSeatId)
	{
		vector<shared_ptr<Seat>> seats;

		for (startSeatId; startSeatId <= endSeatId; startSeatId++)
		{
			seats.push_back(make_shared<Seat>(seatType, rowId, startSeatId));
		}

		return seats;
	}
};

```

```cpp

class IScreenHall
{
public:
	virtual void createSeats(SeatType seatType, string rowId, int startSeatId, int endSeatId) = 0;
	virtual void updatePrice(SeatType seatType, double price) = 0;
	virtual vector<shared_ptr<Seat>> reserveTickets(string rowId, vector<int> seats) = 0;
	virtual void displaySeatingArrangment() = 0;
	virtual int getScreenHallId() = 0;
	virtual ~IScreenHall() = default;
};

class ScreenHall : public IScreenHall
{
private:
	int screenId;
	map<string, vector<shared_ptr<Seat>>> hallSeatMap;
	map<SeatType, vector<string>> categoryRowMap;

	friend class ScreenHallBuilder;
	ScreenHall(int id):screenId(id){}

	SeatFactory seatFactory;

public:
	void createSeats(SeatType seatType, string rowId, int startSeatId, int endSeatId)
	{
		hallSeatMap[rowId] = seatFactory.CreateSeats(seatType, rowId, startSeatId, endSeatId);
		categoryRowMap[seatType].push_back(rowId);
	}
	void updatePrice(SeatType seatType, double price)
	{
		vector<string> seatRows = categoryRowMap[seatType];

		for (string seatRow : seatRows)
		{
			for (shared_ptr<Seat> seat : hallSeatMap[seatRow])
			{
				seat->setPrice(price);
			}
		}


	}

	vector<shared_ptr<Seat>> reserveTickets(string rowId, vector<int> seats)
	{
		vector<shared_ptr<Seat>> resSeats;

		if (hallSeatMap.find(rowId) != hallSeatMap.end())
		{
			for (int seatId : seats)
			{
				hallSeatMap[rowId][seatId-1]->setSeatReserved();
				resSeats.push_back(hallSeatMap[rowId][seatId - 1]);
			}
		}
		else
		{
			cout << "Row ID: " << rowId << " Not found" << endl;
		}
		return resSeats;
	}

	void displaySeatingArrangment()
	{
		cout << "Screen Hall Id: " << screenId << endl<<endl;
		cout << "Seat Layout "<< endl;
		for (auto kv : hallSeatMap)
		{
			auto [rowId, seats] = kv;

			cout << rowId << "--->";

			for (shared_ptr<Seat> seat : seats)
			{
				cout << seat->getRowSeatId()  << " (" << "\033[1;36m" << seat->getReservationStatusToString() << "\033[0m" << "),  ";
			}

			cout <<"[" << seats[0]->getSeatTypeInString() << " $" << seats[0]->getPrice()<<  "]"<< endl;
		}
		cout << "R: Reserved" << endl;
		cout << endl;
	}

	int getScreenHallId() {
		return screenId;
	}
};

class IScreenHallBuilder
{
public:
	virtual IScreenHallBuilder& addRow(SeatType seatType, string rowId, int startSeatId, int endSeatId) = 0;
	virtual shared_ptr<IScreenHall> build() = 0;
	virtual ~IScreenHallBuilder() = default;
};

class ScreenHallBuilder : public IScreenHallBuilder
{
private:
	shared_ptr<IScreenHall> screenHall;

public:
	ScreenHallBuilder(int screenId){
		screenHall = shared_ptr<IScreenHall>(new ScreenHall(screenId));
	}

	IScreenHallBuilder& addRow(SeatType seatType, string rowId, int startSeatId, int endSeatId) {
		screenHall->createSeats(seatType, rowId, startSeatId, endSeatId);
		return *this;
	}

	shared_ptr<IScreenHall> build() {
		return screenHall;
	}
};

```

```cpp

class Movie {
private:
	int movieId;
	string movieName;

public:
	Movie() {}
	Movie(int id, string name):movieId(id), movieName(name){}

	int getMovieId() { return movieId; }
	string getMovieName() { return movieName; }

	string toString() {
		cout << "Movie Id: " << movieId << " Movie Name: " << movieName << endl;
	}
};


```

```cpp

class ShowTime
{
private:
	int showHour;
	int showMinute;
	int showDuration;

public:
	ShowTime() {}
	ShowTime(int hour, int min, int duration)
		:showHour(hour), showMinute(min), showDuration(duration)
	{}

	tuple<int,int, int> getShowTime() { return make_tuple(showHour, showMinute, showDuration); }

};

enum class ShowStatus
{
	Running,
	Cancelled,
	CommingSoon
};

class IShow
{

public:
	virtual void updateShowPrice(SeatType seatType, double price) = 0;
	virtual int getTotalReservedSeats() = 0;
	virtual vector<shared_ptr<Seat>> getAllReservedSeats() = 0;
	virtual void displayShowDetails() = 0;
	virtual vector<shared_ptr<Seat>> reserveSeats(string rowId, vector<int> seats) = 0;
	virtual int getShowId() = 0;
	virtual Movie getMovie() = 0;
	virtual ShowTime getShowTime() = 0;
	virtual shared_ptr<IScreenHall> getScreenHall() = 0;
	virtual ShowStatus getShowStatus() = 0;
	virtual ~IShow() = default;
};

class Show : public IShow
{
private:
	int showId;
	Movie showMovie;
	ShowTime showTime;
	shared_ptr<IScreenHall> screenHall;
	vector<shared_ptr<Seat>> reservedSeats;
	ShowStatus showStatus;

	friend class ShowPlanner;

	Show(int id, ShowTime showtime, Movie movie, shared_ptr<IScreenHall> screenhall )
		:showId(id), showTime(showtime),showMovie(movie), screenHall(screenhall),
		showStatus(ShowStatus::Running)
	{}

	void updateShowPrice(SeatType seatType, double price)
	{
		screenHall->updatePrice(seatType, price);
	}

public:

	int getTotalReservedSeats() override
	{
		// code to get total reserved seats
		return reservedSeats.size();
	}
	vector<shared_ptr<Seat>> getAllReservedSeats() override
	{
		// code to get all reserved seats
		return reservedSeats;
	}

	void displayShowDetails() override
	{
		auto [showHr, showMn, showDur] = showTime.getShowTime();
		cout << "Show ID: " << showId << endl;
		cout << "Movie Name: " << showMovie.getMovieName() << endl;
		cout << "Show Time: " << showHr << ":" << showMn << ", Duration: " << showDur << endl;
		screenHall->displaySeatingArrangment();

		cout << endl;
	}

	vector<shared_ptr<Seat>> reserveSeats(string rowId, vector<int> seats) override
	{
		vector<shared_ptr<Seat>> rseats = screenHall->reserveTickets(rowId, seats);
		for (shared_ptr<Seat> seat : rseats)
		{
			reservedSeats.push_back(seat);
		}

		return rseats;
	}

	int getShowId() { return showId; }

	Movie getMovie()
	{
		return showMovie;
	}
	ShowTime getShowTime()
	{
		return showTime;
	}
	shared_ptr<IScreenHall> getScreenHall()
	{
		return screenHall;
	}

	ShowStatus getShowStatus() { return showStatus; }

	void cancelShow() {
		// complex cancellation show logic
		// Reset all the book seat status
		// set showStatus = ShowStatus::Cancelled
	}

};

class ShowPlanner
{
protected:
	shared_ptr<IShow> show;
public:
	ShowPlanner(int id, ShowTime showTime, Movie movie, shared_ptr<IScreenHall> screenHall)
		:show(shared_ptr<IShow>(new Show(id,showTime,movie,screenHall)))
	{
	}

	virtual ShowPlanner& updateShowPrice(SeatType showType, double price) = 0;
	virtual shared_ptr<IShow> create() = 0;
	virtual ~ShowPlanner() = default;
};

class ShowPlannerImpl : public ShowPlanner
{
public:
	ShowPlannerImpl(int id, ShowTime showTime, Movie movie, shared_ptr<IScreenHall> screenHall)
		:ShowPlanner(id,showTime,movie,screenHall)
	{}

	ShowPlanner& updateShowPrice(SeatType showType, double price)
	{
		show->updateShowPrice(showType, price);
		return *this;
	}

	shared_ptr<IShow> create() {
		return show;
	}
};

```

```cpp

class Payment
{
public:
	virtual bool processPayment(double amount) = 0;
	virtual ~Payment() = default;

};

class CreditCardPayment : public Payment
{
public:
	bool processPayment(double amount) {
		cout << "****** Processing Credit Card Payment of $" << amount << endl;
		cout << endl;
		return true;
	}
};

class PayPalPayment : public Payment
{
public:
	bool processPayment(double amount) {
		cout << "****** Processing PayPal Payment of $" << amount << endl;
		cout << endl;
		return true;
	}
};

class StripPayment : public Payment
{
public:
	bool processPayment(double amount) {
		cout << " ****** Processing Strip Payment of $" << amount << endl;
		cout << endl;
		return true;
	}
};

class PaymentManager
{
private:
	shared_ptr<Payment> paymentStrategy;

public:
	PaymentManager(shared_ptr<Payment> paymentstrategy)
		:paymentStrategy(paymentstrategy)
	{}

	bool makePayment(double amount) {
		return paymentStrategy->processPayment(amount);
	}
};

```

```cpp

class Ticket
{
private:
	int ticketId;
	int showId;
	string movieName;
	ShowTime showTime;
	int screenId;
	vector<shared_ptr<Seat>> resSeats;
	double totalBookingAmount;
	string customerFullName;
	string mobileNo;
	int theaterId;
	string theaterName;
	string theaterAddress;

	friend class BookingManager;

	Ticket(int id, int showid, string moviename, ShowTime showtime, int screenid)
		:ticketId(id), showId(showid), movieName(moviename), showTime(showtime), screenId(screenid),
		totalBookingAmount(0.0), customerFullName(""), mobileNo("")
	{}

	void setTheaterDetails(int id, string name, string address) {
		theaterId = id;
		theaterName = name;
		theaterAddress = address;
	}

	void setReservedSeats(vector<shared_ptr<Seat>> seats) {
		resSeats = seats;
	}

	double calculateTotalBookingAmount() {
		totalBookingAmount = 0.0;

		for (shared_ptr<Seat> seat : resSeats) {
			totalBookingAmount = totalBookingAmount + seat->getPrice();
		}

		return totalBookingAmount;
	}

	void setCustomerData(string fullName, string mobile) {
		customerFullName = fullName;
		mobileNo = mobile;
	}

public:
	void printTicket()
	{
		auto [showHr, showMn, showDur] = showTime.getShowTime();
		cout << "Ticket ID: " <<ticketId << endl;
		cout << "Name: " << customerFullName << ", Mobile: " << mobileNo << endl;
		cout << "Theater Name: " << theaterName << ", Address: " << theaterAddress << endl;
		cout << "Show Id:" << showId << endl;
		cout << "Screen Id:" << screenId << endl;
		cout << "Movie Name:" << movieName << endl;
		cout << "Show Time: " << showHr << ":" << showMn << " , Show Duration: " << showDur << endl;
		cout << "Seats:";
		for (shared_ptr<Seat> seat : resSeats) {
			cout << seat->getSeatId() << " ,";
		}

		cout << "Total Amount Paid:" << totalBookingAmount << endl;

		cout << endl;
	}

	void cancelTicket() {
		for (shared_ptr<Seat> seat : resSeats) {
			seat->setSeatUnreserved();
		}

		//cout << "Ticket ID: " << ticketId <<" has been cancelled" << endl;
		cout << "\033[1;31m" << "Ticket ID: " << ticketId << " has been cancelled" << "\033[0m" << endl;
		cout << endl;
		// more complex cancellation logic

	}
};

class BookingManager
{
private:
	shared_ptr<Ticket> ticket;
	shared_ptr<IShow> show;
public:
	BookingManager(int ticketId, shared_ptr<Theater> theater, shared_ptr<IShow> show)
	{
		ticket = shared_ptr<Ticket>(new Ticket(ticketId,show->getShowId(),
			show->getMovie().getMovieName(), show->getShowTime(), show->getScreenHall()->getScreenHallId()));
		ticket->setTheaterDetails(theater->getTheaterId(), theater->getTheaterName(), theater->getTheaterAddress());
		this->show = show;
	}

	BookingManager& reservedSeats(string rowId, vector<int> seats)
	{
		vector<shared_ptr<Seat>> resSeats = show->reserveSeats(rowId, seats);
		ticket->setReservedSeats(resSeats);
		return *this;
	}

	BookingManager& addCustomerData(string fullname, string mobile) {
		ticket->setCustomerData(fullname, mobile);
		return *this;
	}

	shared_ptr<Ticket> PayAndBook(shared_ptr<Payment> paymentStrategy) {
		double ticketAmount = ticket->calculateTotalBookingAmount();
		PaymentManager payManager(paymentStrategy);
		payManager.makePayment(ticketAmount);
		return ticket;
	}
};

```

```cpp

class Theater {
private:
	int theaterId;
	string theaterName;
	string theaterAddress;

	vector<shared_ptr<IScreenHall>> screenHalls;
	vector<shared_ptr<IShow>> shows;
	vector<shared_ptr<Movie>> movies;

public:

	Theater(int id, string name, string address)
		:theaterId(id), theaterName(name), theaterAddress(address)
	{}

	void addScreenHall(shared_ptr<IScreenHall> screenHall) {
		screenHalls.push_back(screenHall);
	}

	void addShow(shared_ptr<IShow> show) {
		shows.push_back(show);
	}

	void addMovie(shared_ptr<Movie> movie) {
		movies.push_back(movie);
	}

	vector<shared_ptr<IScreenHall>> getAllScreenHalls() {
		return screenHalls;
	}

	vector<shared_ptr<IShow>> getAllRunningShows() {

		vector<shared_ptr<IShow>> runningShows;

		for (shared_ptr<IShow> show : shows)
		{
			if (show->getShowStatus() == ShowStatus::Running) {
				runningShows.push_back(show);
			}
		}

		return runningShows;
	}

	shared_ptr<IShow> getShowById(int showId) {

		for (shared_ptr<IShow> show : shows) {
			if (show->getShowId() == showId) {
				return show;
			}
		}

		return nullptr;

	}

	int getTheaterId() { return theaterId; }
	string getTheaterName() { return theaterName; }
	string getTheaterAddress() { return theaterAddress; }

};

class City
{
private:
	int cityId;
	string cityName;
	vector<shared_ptr<Theater>> theaters;

public:
	City(int id, string name) :cityId(id), cityName(name) {}

	void addTheater(shared_ptr<Theater> theater) {
		theaters.push_back(theater);
	}

	vector<shared_ptr<Theater>> getAllTheater() {
		return theaters;
	}

};

```

```cpp

int main()
{
	// Create few Movie objects
	Movie inception(1, "Inception");
	Movie batman(2, "Batman");

	City newyork(1, "New York");
	City toronto(2, "Toronto");

	shared_ptr<Theater> cineplex = make_shared<Theater>(1, "Cineplex", "Downtown, Toronto");
	shared_ptr<Theater> cinepolis = make_shared<Theater>(2, "Cinepolis", "Downtown, New York");

	shared_ptr<IScreenHall> cineplex_hall1 = ScreenHallBuilder(101)
		.addRow(SeatType::Gold, "A", 1, 10)
		.addRow(SeatType::Gold, "B", 1, 10)
		.addRow(SeatType::Silver, "C", 1, 10)
		.addRow(SeatType::Silver, "D", 1, 10)
		.build();

	shared_ptr<IScreenHall> cineplex_hall2 = ScreenHallBuilder(102)
		.addRow(SeatType::Vip, "A", 1, 8)
		.addRow(SeatType::Premium, "B", 1, 10)
		.addRow(SeatType::Executive, "C", 1, 10)
		.addRow(SeatType::Executive, "D", 1, 10)
		.addRow(SeatType::Standard, "D", 1, 10)
		.build();

	cineplex->addScreenHall(cineplex_hall1);
	cineplex->addScreenHall(cineplex_hall2);

	ShowTime morning(10, 0, 120);
	ShowTime afternoon(12, 30, 150);
	ShowTime evening(18, 0, 120);
	ShowTime night(20, 30, 150);

	shared_ptr<IShow> incp_cine_h1_morn = ShowPlannerImpl(1001, morning, inception, cineplex_hall1)
		.updateShowPrice(SeatType::Gold, 20)
		.updateShowPrice(SeatType::Silver, 15)
		.create();

	shared_ptr<IShow> batman_cine_h2_night = ShowPlannerImpl(1002, night, batman, cineplex_hall2)
		.updateShowPrice(SeatType::Vip, 35)
		.updateShowPrice(SeatType::Premium, 30)
		.updateShowPrice(SeatType::Executive, 25)
		.updateShowPrice(SeatType::Standard, 20)
		.create();

	cineplex->addShow(incp_cine_h1_morn);
	cineplex->addShow(batman_cine_h2_night);

	shared_ptr<Ticket> t1 = BookingManager(10001, cineplex,cineplex->getShowById(1001))
		.reservedSeats("A", { 4,5,6 })
		.addCustomerData("Linda McCarty", "+1-637-765-4567")
		.PayAndBook(make_shared<CreditCardPayment>());

	t1->printTicket();

	incp_cine_h1_morn->displayShowDetails();

	shared_ptr<Ticket> t2 = BookingManager(10002, cineplex, cineplex->getShowById(1002))
		.reservedSeats("C", { 7,8,9 })
		.addCustomerData("Dorothy Levy", "+1-435-765-1122")
		.PayAndBook(make_shared<PayPalPayment>());

	shared_ptr<Ticket> t3 = BookingManager(10003, cineplex, cineplex->getShowById(1002))
		.reservedSeats("B", { 4,5 })
		.addCustomerData("Raya Velasquez", "+1-321-234-3322")
		.PayAndBook(make_shared<StripPayment>());

	t2->printTicket();
	t3->printTicket();

	batman_cine_h2_night->displayShowDetails();

	t2->cancelTicket();

	batman_cine_h2_night->displayShowDetails();

	return 0;
}

```
