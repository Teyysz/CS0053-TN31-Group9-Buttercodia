# Buttercodia Parking

Buttercodia Parking is a console-based C++ application for managing parking space rentals. Users can check parking rates, choose an available slot, create a rental, and view rental records. The program saves records in a local text file so they remain available after restarting.

This is our group project for **CS0053 – Programming Tools and Techniques, Section TN31**.

## Current Features

- View hourly rates for Economy, Business, and First Class parking.
- Display available and occupied slots when creating a rental. Each tier has 100 slots.
- Create a rental with a customer name, plate number, parking tier, slot, and rental duration.
- Record a payment method: cash, card, or e-wallet.
- Calculate the total rental cost and assign a rental number starting at R1001.
- View saved rentals, including their active or completed status.
- Save and load rental records using a local text file.
- Mark expired rentals as completed and release their slots when the program starts or returns to the menu.

Payment options only record payment information. The program does not process actual payments. For cards, it asks for the last four digits only.

## Parking Rates

| Parking Tier | Rate per Hour | Slots |
|---|---:|---:|
| Economy | PHP 35 | 100 |
| Business | PHP 55 | 100 |
| First Class | PHP 85 | 100 |

**Total cost = hourly rate × number of hours**

For example, an Economy rental for 2 hours costs PHP 70.

## Requirements

- A G++ compiler with C++17 support.
- A terminal to compile and run the application.
- VS Code with the C/C++ extension for the project development workflow.
- Git and GitHub for group collaboration.

On Windows, G++ can be provided by MinGW-w64 or MSYS2. Make sure `g++` is available in your terminal:

```sh
g++ --version
```

## Source Files

Keep the four source folders together in the project root. The code uses relative include paths between them.

| File | Purpose |
|---|---|
| `Theo/main.cpp` | Main menu, startup, and program integration |
| `Daniel/parking_slots.cpp` and `parking_slots.h` | Parking rates, slot display, and occupancy tracking |
| `Odda/storage.cpp` and `storage.h` | Rental data structures, file storage, rental numbers, and expiration handling |
| `Partick/reservations.cpp` and `reservations.h` | Rental creation, payment information, rental display, and input helpers |

The folder name `Partick` matches the current source files and compilation commands.

## Compilation and Execution

Open a terminal in the project root, where the `Theo`, `Daniel`, `Odda`, and `Partick` folders are located. All four `.cpp` files must be compiled together.

### Windows PowerShell or Command Prompt

Compile:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic Theo/main.cpp Daniel/parking_slots.cpp Odda/storage.cpp Partick/reservations.cpp -o buttercodia.exe
```

Run:

```powershell
.\buttercodia.exe
```

### Linux or macOS with G++ Available

Compile:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic Theo/main.cpp Daniel/parking_slots.cpp Odda/storage.cpp Partick/reservations.cpp -o buttercodia
```

Run:

```sh
./buttercodia
```

## Using the Program

The main menu provides these options:

```text
--------------- MENU ---------------
1. View parking rates
2. Rent a parking space
3. View parking rentals
4. Exit
------------------------------------
```

To create a rental, select option 2, choose a parking tier and an available slot, then enter the customer and payment information. Enter `1` at the final confirmation prompt to save the rental. Entering `0` at the tier or slot prompt cancels the rental process.

The slot display uses `O` for available and `X` for occupied. Rentals can be viewed using option 3.

## Sample Input and Output

Example inputs for a new rental in an empty database:

| Prompt | Input |
|---|---|
| Main menu option | `2` |
| Parking tier | `1` — Economy |
| Parking slot | `1` |
| Customer name | `Theo Nadela` |
| Plate number | `ABC1234` |
| Number of hours | `2` |
| Payment method | `1` — Cash |
| Confirm rental | `1` |

The resulting confirmation includes:

```text
Rental R1001 | Theo Nadela | Economy | Slot 1 | Total P70.00
Parking space rental created successfully! Rental number: R1001
```

Viewing the rental list then includes:

```text
R1001 | ACTIVE | Theo Nadela | ABC1234 | Economy | Slot 1 | 2 hours | Cash | P70.00
```

The rental number and slot availability depend on previously saved records.

## Data Storage

The program uses `buttercodia_database.txt` in the terminal's current working directory. Run the application from the same directory each time to load the same records. The file is created when the program saves data, including during startup.

Records use the following pipe-separated format:

```text
rentalNumber|name|plate|tier|paymentMethod|paymentDetails|slot|hours|total|startTime|status
```

The start time is stored as a Unix timestamp, and the status is `ACTIVE` or `COMPLETED`. Expiration checks run at startup and before each main menu display; they do not run continuously while the program waits for input.

## Group Responsibilities

| Member | Main Responsibility |
|---|---|
| Theo | Main menu and program integration |
| Daniel | Parking rates, slot display, and occupancy tracking |
| Patrick | Rental transactions, payment information, and input handling |
| Odda | File storage, rental records, and expiration handling |

These responsibilities describe the current code division. Each member must also contribute to testing, GitHub collaboration, and explaining their own code during the defense.

## Current Limitations and Remaining Work

- The main menu currently has three user-facing features. At least two more are needed to meet the project requirement of five. Possible additions are searching rentals and ending or cancelling an existing rental.
- Input validation needs improvement for blank customer details, invalid payment choices, numeric input with trailing characters, and excessively large rental durations.
- Text fields must not contain `|`, because it is used to separate saved fields and is not escaped by the current program.
- Malformed numeric values in the database can cause loading to fail with an uncaught exception.
- File-saving failures are not currently reported to the user.
- The exit message still uses the earlier name `ParkClass`.

Formatter evidence, static-analysis findings, debugger evidence, test results, AI interaction logs, and individual GitHub contributions must be recorded from actual group work. They are not established by this README.

## Repository and Submission

Use a shared repository named `CS0053-TN31-GroupXX-ProjectName`, replacing the placeholders with the group's details.

Each member needs at least one feature branch, three meaningful commits, and one pull request reviewed by another member before merging. Include a `.gitignore` that excludes compiled executables and temporary build files. Use fictional customer and payment details for shared examples.

The final submission requires the GitHub repository URL and a group report in PDF format. The group must also demonstrate the application and development workflow, with each member explaining their own contribution.
