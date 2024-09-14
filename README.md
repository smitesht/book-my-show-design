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



