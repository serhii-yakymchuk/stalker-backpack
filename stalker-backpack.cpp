#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

bool is_running = true;

struct Item {
    int modyfy;
    std::string name; 
    int power;       
    std::string rarity;   
};

std::vector<Item> items;

int rundom_num (int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

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
        if (items[i].modyfy == 0) {
            std::cout << i+1 << ". " << items[i].name << " [Сила: " << items[i].power << "] | Рідкість: " << items[i].rarity << "\n";
        }else{
            std::cout << i+1 << ". [+" << items[i].modyfy << "] " << items[i].name << " [Сила: " << items[i].power << "] | Рідкість: " << items[i].rarity << "\n";
        }
        
    }   
    std::cout << "-----------------------\n";
}

void push(){
    if (items.size() == 5) {
        std::cout << "Рюкзак заповнений! Треба щось викинути.\n";
    } else {
        std::cout << "Ви хочете покласти: ";
        std::cin.ignore(); // Очищаємо буфер перед getline
        std::string name;
        std::getline(std::cin, name);
        items.push_back({0, name, rundom_num(1, 10), "Звичайна"});
        clear_screen();
        std::cout << "\"" << name << "\" успішно заховано в рюкзак.\n";
    }
}

void craft(){
    if (items.empty()) {
        std::cout << "Твій рюкзак порожній, немає чого модифікувати!\n";
        return;
    }
    std::cout << "Напишіть номер предмету, який хочете модифікувати\n";
    show_item();
    int i = get_num(1, items.size());
    items[i-1].modyfy++;
    items[i-1].power += 10;
    items[i-1].rarity = "модифікована";
    clear_screen();
    std::cout << "\"" << items[i-1].name << "\" успішно модифіковано.\n";
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
    std::cout << "\"" << items[index_to_delete].name << "\" успішно викинуто.\n";
    items.erase(items.begin() + index_to_delete);
}

void save(const std::vector<Item>& itms) {
    std::ofstream out("save.txt");
    if (out.is_open()) {
        for (size_t i = 0; i < itms.size(); i++ ){
            out << itms[i].modyfy << "\n";
            out << itms[i].name << "\n";
            out << itms[i].power << "\n";
            out << itms[i].rarity << "\n";
        }
        out.close(); // Після роботи файл ТРЕБА закрити
    }
}
void download(std::vector<Item>& itms) {
    std::ifstream in("save.txt");
    if (in.is_open()) {

        int modyfy;
        std::string name;
        int power;
        std::string rarity;

        itms.clear();

        while (in >> modyfy) {
            in.ignore();
            std::getline(in, name); // Тепер спокійно читаємо назву з пробілами повністю
            
            in >> power;
            in.ignore(); // Знову чистимо буфер після числа
            
            std::getline(in, rarity); // Читаємо рідкість
            
            itms.push_back({modyfy, name, power, rarity});
        }
        in.close();
    }
}

void handle_menu() {
    std::string input;
    std::cout << "\nВибери дію (1-5):\n";
    std::cout << "1 - показати вміст рюкзака\n";
    std::cout << "2 - покласти річ в рюкзак\n";
    std::cout << "3 - модифікувати зброю\n";
    std::cout << "4 - забрати річ з рюкзака\n";
    std::cout << "5 - вийти з гри\n";
    std::cout << "6 - вийти з гри та зберегти\n";
    std::cout << "7 - завантажити гру\n";
    std::cout << "Твій вибір: ";
    
    int choice = get_num(1, 7);

    switch (choice) {
        case 1:
            clear_screen();
            show_item();
            break;
        case 2:
            clear_screen();
            push();
            break;
        case 3:
            clear_screen();
            craft();
            break;
        case 4:
            clear_screen();
            delete_item();
            break;
        case 5:
            clear_screen();
            std::cout << "Бувай, сталкере! Вдалого полювання за артефактами.\n";
            is_running = false;
            break;
        case 6:
            clear_screen();
            save(items);
            std::cout << "Бувай, сталкере! Вдалого полювання за артефактами.\n";
            is_running = false;
            break;
        case 7:
            clear_screen();
            download(items);
            std::cout << "з поверненням!.\n";
            break;
        default:
            clear_screen();
            std::cout << "Неправильний вибір! Дозволені тільки цифри 1 - 7.\n";
            break;
    }
}

int main() {

    items.push_back({0, "Ніж", 15, "Звичайна"});

    clear_screen();
    std::cout << "Вітаємо у грі \"Рюкзак сталкера\"!\n";
    while (is_running) {
        handle_menu();
    }
    return 0;
}
