#include <iostream>
#include <string>
#include <vector>

bool is_running = true;

std::vector<std::string> items;

int get_num(int min, int max) {
    std::string input;
    int number;

    while (true) {
        std::cout << "Введи число від " << min << " до " << max << ": ";
        std::cin >> input;

        try {
            // Пробуємо перетворити рядок в число
            size_t processed_chars;
            number = std::stoi(input, &processed_chars);

            // Перевіряємо, чи весь рядок був числом (щоб відсікти варіанти типу "12abc")
            if (processed_chars != input.length()) {
                std::cout << "Помилка! Дозволені тільки чисті цифри без букв.\n";
                continue;
            }

            // Перевіряємо діапазон
            if (number >= min && number <= max) {
                return number; // Все супер, повертаємо чисте число і виходимо з функції
            } else {
                std::cout << "Помилка! Число поза діапазоном. Спробуй ще раз.\n";
            }

        } catch (const std::invalid_argument&) {
            // Спрацює, якщо ввели чисті букви (наприклад, "abc")
            std::cout << "Це взагалі не число! Спробуй ще раз.\n";
        } catch (const std::out_of_range&) {
            // Спрацює, це якщо ввели щось величезне, що не влазить в int
            std::cout << "Число занадто велике чи занадто мале!\n";
        }
    }
}

void clear_screen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

void show_item(){
    if (items.empty()) {
        std::cout << "Твій рюкзак порожній, як кишені новічка.\n";
        return;
    }
    std::cout << "--- Вміст рюкзака (" << items.size() << "/5) ---\n";
    for (size_t i = 0; i < items.size(); i++) {
        std::cout << i+1 << ". " << items[i] << "\n";
    }   
    std::cout << "-----------------------\n";
}

void push(){
    if (items.size() == 5) {
        std::cout << "Рюкзак заповнений! Треба щось викинути.\n";
    } else {
        std::cout << "Ви хочете покласти: ";
        std::cin.ignore(); // Очищаємо буфер перед getline
        std::string str;
        std::getline(std::cin, str);
        items.push_back(str);
        clear_screen();
        std::cout << "\"" << str << "\" успішно заховано в рюкзак.\n";
    }
}

void delete_item(){
    if (items.empty()) {
        std::cout << "Твій рюкзак порожній, нічого викидати!\n";
        return;
    }

    std::cout << "Напишіть номер предмету, який хочете забрати\n";
    show_item();
    
    // Віднімаємо 1, бо юзер вводить від 1, а вектор рахує від 0
    int index_to_delete = get_num(1, items.size()) - 1;
    
    clear_screen();
    std::cout << "\"" << items[index_to_delete] << "\" успішно викинуто.\n";
    items.erase(items.begin() + index_to_delete);
}

void handle_menu() {
    std::string input;
    std::cout << "\nВибери дію (1-4):\n";
    std::cout << "1 - показати вміст рюкзака\n";
    std::cout << "2 - покласти річ в рюкзак\n";
    std::cout << "3 - забрати річ з рюкзака\n";
    std::cout << "4 - вийти з гри\n";
    std::cout << "Твій вибір: ";
    
    std::cin >> input;
    if (input.length() != 1) {
        clear_screen();
        std::cout << "Помилка! Треба ввести лише одну цифру від 1 до 4.\n";
        return;
    }
    char choice = input[0];

    switch (choice) {
        case '1':
            clear_screen();
            show_item();
            break;
        case '2':
            clear_screen();
            push();
            break;
        case '3':
            clear_screen();
            delete_item();
            break;
        case '4':
            clear_screen();
            std::cout << "Бувай, сталкере! Вдалого полювання за артефактами.\n";
            is_running = false;
            break;
        default:
            clear_screen();
            std::cout << "Неправильний вибір! Дозволені тільки цифри 1, 2, 3 або 4.\n";
            break;
    }
}

int main() {
    clear_screen();
    std::cout << "Вітаємо у грі \"Рюкзак сталкера\"!\n";
    while (is_running) {
        handle_menu();
    }
    return 0;
}