#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <tuple>

// Cursor And Text Colour Section..
void setCursorPosition(int x, int y) // Used to change cursor location.
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, position);
}

void setcolor(int color) // Used to change text colour of console.
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
}

// Frame Section..
void draw_horizontal_frame(int width)
{
    std::cout << "+";
    for (int i = 0; i < width; i++)
    {
        std::cout << "-";
    }
    std::cout << "+\n";
}

void draw_frame()
{
    system("CLS");
    int frameX = 0;
    int frameY = 0;
    setCursorPosition(frameX, frameY);
    int frame_width = 30;
    int frame_height = 10;
    draw_horizontal_frame(frame_width);
    for (int i = 1; i < frame_height; i++)
    {
        setCursorPosition(frameX, i);
        std::cout << "|";
        setCursorPosition(frame_width + 1, i);
        std::cout << "|";
    }
    setCursorPosition(frameX, 10);
    draw_horizontal_frame(frame_width);
}

void extend_frame() // Used to extend frame when game starts.
{
    setcolor(15);
    int positionX = 0;
    int positionY = 11;
    setCursorPosition(positionX, positionY);
    for (int i = 0; i < 1; i++)
    {
        std::cout << "|";
        setCursorPosition(31, positionY);
        std::cout << "|";
        setCursorPosition(positionX, ++positionY);
    }
    draw_horizontal_frame(30);
}

// Function to calculate size of array...
// this is a template function to calculate size of array and return its size.
// template function allows us to create a function tamplate and use it for different
// datatypes which helps us in code reusability and maintainability.
template <typename T, size_t N>
constexpr size_t arrayLength(T (&)[N])
{
    return N;
}

// Clear_frane function to clear the content within frame.
void clear_frame(int positionX=1,int positionY=1)
{
    int y = positionY;
    setCursorPosition(positionX, positionY);
    for (int i = 0; i < 10-y; i++)
    {
        for (int j = 1; j < 30; j++)
        {
            setCursorPosition(j, positionY);
            std::cout << " ";
        }
        positionX = 1;
        setCursorPosition(positionX, ++positionY);
    }
    setCursorPosition(1, 1);
}

// Print function to print the text content within frame.
void print(std::string *arr, int l,int positionY=1,int positionX=1)
{
    clear_frame(positionX,positionY);
    positionY=(10 - l) / 2;
    if (l % 2 != 0)
    {
        positionY++;
    }
    setCursorPosition(positionX, positionY);
    for (int i = 0; i < l; i++)
    {
        std::cout << std::setw(((30 - arr[i].length()) / 2) + arr[i].length()) << arr[i];
        setCursorPosition(positionX, ++positionY);
    }
}

// Greet Function.
void greet()
{
    std::string greet_arr[] = {"Welcome", "to", "GUESS", "THE", "NUMBER"};
    setcolor(14);
    int length = arrayLength(greet_arr);
    print(greet_arr, length);
    Sleep(2000);
}

// Game Management.
std::tuple<int, int> select_game()
{
    std::string level[] = {"Select A Game!!", "Press", "1. Eazy", "2. Medium", "3. Hard"};
    std::string eazy_description[] = {"Guess Number", "From", "1 to 100"};
    std::string medium_description[] = {"Guess Number", "From", "1 to 500"};
    std::string hard_description[] = {"Guess Number", "From", "1 to 1000"};
    std::string *selection[] = {eazy_description, medium_description, hard_description};
    // std::string rules[]={"You will get","10 Chance","to Guess The Number"}
    print(level, arrayLength(level));
    int selected_toughness;
    int max_number, num_chances;
    std::string game;
    selected_toughness = getch();
    if (int(selected_toughness) == 49)
    {
        max_number = 100;
        num_chances = 7;
        game = "Eazy";
        selected_toughness=0;
    }
    else if (int(selected_toughness) == 50)
    {
        max_number = 500;
        num_chances = 7;
        game = "Medium";
        selected_toughness=1;
    }
    else if (int(selected_toughness) == 51)
    {
        max_number = 1000;
        num_chances = 10;
        game = "Hard";
        selected_toughness=2;
    }
    else
    {
        clear_frame();
        setCursorPosition(1, 5);
        std::string message = "Incorrect Choice!";
        std::cout << std::setw((30 - message.length()) / 2 + message.length()) << message;
        Sleep(1000);
        select_game();
    }
    print(selection[selected_toughness],3);
    setCursorPosition(3, 1);
    std::cout << "Chances: " << num_chances;
    setCursorPosition(23, 1);
    std::cout << std::setw(6) << game;
    setCursorPosition(1, 12);
    extend_frame();
    return std::make_tuple(max_number, num_chances);
}

void play()
{
    auto result = select_game();
    int cgn = rand() % std::get<0>(result) + 1; // cgn=computer Guessed Number....
    int chances = std::get<1>(result);
    int input_number;
    std::string content[]={"Guess Number","from","(1 to "+std::to_string(std::get<0>(result))+")"};
    std::string less_than[]={"Less than that!!"};
    std::string greater_than[]={"Greater than that!!"};
    std::string winning_message[]={"!!! Heyyy You Won !!!"};
    std::string better_luck_message[]={"Better Luck","Next Time..."};
    while (chances!=0)
    {
        setcolor(14);
        print(content,arrayLength(content),3);
        setCursorPosition(1,11);
        std::cout<<"                              ";  //Cleaning input area.
        setCursorPosition(1,11);
        std::cout<<" Enter Number: ";
        std::cin>>input_number;
        setCursorPosition(12,1); // Decreasing Chances..
        std::cout<<"  ";
        setCursorPosition(12,1);
        std::cout<<--chances;
        if(chances==0 && input_number!=cgn)
        {
            setcolor(5);
            print(better_luck_message,arrayLength(better_luck_message));
            break;
        }
        else if(input_number<cgn)
        {
            setcolor(10);
            print(greater_than,1,3);
        }
        else if(input_number>cgn)
        {
            setcolor(10);
            print(less_than,1,3);
        }
        else
        {
            setcolor(10);
            print(winning_message,arrayLength(winning_message));
            break;
        }
        Sleep(2000);
    }
    int positionY=11;
    for(int i=0; i<2; i++)
    {
        setCursorPosition(0,positionY++);
        std::cout<<std::setfill(' ')<<std::setw(35)<<"\n";
    }
    Sleep(3000);
}

void ask_to_play()
{
    while(1){
        setcolor(14);
        std::string ask_array[] = {"Press\"ENTER\"", "to Play!", "(Else Press Any key)"};
        int length = arrayLength(ask_array);
        print(ask_array, length);
        int ask;
        ask = getch();
        if (ask == 13)
        {
            play();
        }
        else
        {
            std::string thanks[]={"Thank for","Playing"};
            print(thanks,arrayLength(thanks));
            Sleep(1500);
            break;
        }
    }
}

int main()
{
    draw_frame();
    greet();
    ask_to_play();
    system("CLS");
    return 0;
}