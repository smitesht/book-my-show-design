#include <iostream>
#include <memory>
#include "./seats/Seat.cpp"
#include "./screen/ScreenHall.cpp"
#include "./screen/ScreenHallBuilder.cpp"
#include "./show/ShowTime.cpp"
#include "./show/Show.cpp"
#include "./show/ShowPlannerImpl.cpp"
#include "./payment/PaymentTypes.cpp"
#include "./payment/PaymentManager.cpp"
#include "Movie.cpp"
#include "City.cpp"
#include "Theater.cpp"
#include "Ticket.cpp"
#include "BookingManager.cpp"


using namespace std;

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