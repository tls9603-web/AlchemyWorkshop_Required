#include <iostream>
#include <vector>
#include <string>

// PotionRecipe 클래스: 하나의 물약 레시피 정보를 담는 클래스
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients;

    // 생성자: 물약 이름과 재료 목록을 받아 객체를 초기화합니다.
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리하고 관련 기능을 제공하는 클래스
class AlchemyWorkshop {
private:
    // PotionRecipe 객체들을 저장할 벡터(동적 배열)
    std::vector<PotionRecipe> recipes;

public:
    // 레시피를 추가하는 메서드
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피를 화면에 출력하는 메서드
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        // for 루프를 사용해 저장된 모든 레시피를 순회합니다.
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 한 레시피에 포함된 모든 재료를 순회하며 출력합니다.
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    // --- [필수 기능] 물약 이름으로 레시피 검색 ---
    // const 키워드: 이 함수는 멤버 변수(recipes)를 수정하지 않는다는 의미
    void searchByPotionName(const std::string& name) const {
        bool found = false; // 검색 성공 여부를 저장할 변수

        std::cout << "\n--- [ '" << name << "' 물약 이름으로 검색 결과 ] ---" << std::endl;

        // 모든 레시피를 처음부터 끝까지 확인합니다.
        for (size_t i = 0; i < recipes.size(); ++i) {
            // 현재 확인 중인 레시피의 이름(recipes[i].potionName)과
            // 사용자가 입력한 이름(name)이 같은지 비교합니다.
            if (recipes[i].potionName == name) {
                // 이름이 같다면, 해당 레시피 정보를 출력합니다.
                std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
                std::cout << "  > 필요 재료: ";
                for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                    std::cout << recipes[i].ingredients[j];
                    if (j < recipes[i].ingredients.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;

                found = true; // 찾았다고 표시
                break; // 이름은 중복되지 않으므로, 하나 찾으면 더 이상 찾을 필요가 없어 반복문을 종료합니다.
            }
        }

        // for 루프가 끝날 때까지 found가 false라면, 한 번도 레시피를 찾지 못했다는 의미입니다.
        if (!found) {
            std::cout << "해당 이름의 레시피를 찾을 수 없습니다." << std::endl;
        }
        std::cout << "------------------------------------------------\n";
    }

    // --- [필수 기능] 재료로 레시피 검색 ---
    void searchByIngredient(const std::string& ingredient) const {
        bool found = false; // 검색 성공 여부를 저장할 변수

        std::cout << "\n--- [ '" << ingredient << "' 재료 포함 레시피 검색 결과 ] ---" << std::endl;

        // 1. 바깥쪽 for 루프: 모든 레시피를 하나씩 확인합니다.
        for (size_t i = 0; i < recipes.size(); ++i) {
            // 2. 안쪽 for 루프: 현재 레시피(recipes[i])에 포함된 모든 재료를 하나씩 확인합니다.
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                // 현재 확인 중인 재료(recipes[i].ingredients[j])가
                // 사용자가 입력한 재료(ingredient)와 같은지 비교합니다.
                if (recipes[i].ingredients[j] == ingredient) {
                    // 재료가 포함되어 있다면, 레시피 정보를 출력합니다.
                    std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;

                    found = true; // 찾았다고 표시
                    break; // 이 레시피에 해당 재료가 있다는 것을 확인했으니, 더 이상 이 레시피의 다른 재료를 볼 필요가 없습니다. 안쪽 루프만 탈출합니다.
                }
            }
        }

        // 바깥쪽 for 루프까지 모두 끝났을 때 found가 false라면, 어떤 레시피에서도 해당 재료를 찾지 못한 것입니다.
        if (!found) {
            std::cout << "해당 재료를 사용하는 레시피를 찾을 수 없습니다." << std::endl;
        }
        std::cout << "----------------------------------------------------\n";
    }
};

// 프로그램의 실제 실행 흐름을 담당하는 main 함수
int main() {
    AlchemyWorkshop myWorkshop;

    // 테스트를 위한 기본 레시피 추가
    myWorkshop.addRecipe("체력 회복 물약", { "붉은 약초", "정제수" });
    myWorkshop.addRecipe("마나 회복 물약", { "푸른 약초", "정제수" });
    myWorkshop.addRecipe("힘 증폭 물약", { "붉은 약초", "트롤의 피" });

    while (true) {
        std::cout << "⚗️ 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 레시피 검색" << std::endl; // 검색 기능 메뉴 추가
        std::cout << "4. 종료" << std::endl;       // 종료는 4번으로 변경
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        // choice 입력 후 버퍼에 남은 엔터키(\n)를 비워주기 위한 코드.
        // 이것이 없으면 다음에 나올 getline이 바로 종료되어 버립니다.
        std::cin.ignore(10000, '\n');

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::getline(std::cin, name);

            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            // --- 검색 기능 구현 ---
            int search_choice;
            std::cout << "\n--- 검색 옵션 ---" << std::endl;
            std::cout << "1. 물약 이름으로 검색" << std::endl;
            std::cout << "2. 재료로 검색" << std::endl;
            std::cout << "선택: ";
            std::cin >> search_choice;

            if (std::cin.fail()) {
                std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            std::cin.ignore(10000, '\n'); // 숫자 입력 후 버퍼 비우기

            if (search_choice == 1) {
                std::string potion_name_to_search;
                std::cout << "검색할 물약 이름: ";
                std::getline(std::cin, potion_name_to_search);

                // 입력값이 비어있지 않은지 간단히 확인
                if (!potion_name_to_search.empty()) {
                    myWorkshop.searchByPotionName(potion_name_to_search);
                }
                else {
                    std::cout << "검색할 이름을 입력해주세요." << std::endl;
                }
            }
            else if (search_choice == 2) {
                std::string ingredient_to_search;
                std::cout << "검색할 재료 이름: ";
                std::getline(std::cin, ingredient_to_search);

                if (!ingredient_to_search.empty()) {
                    myWorkshop.searchByIngredient(ingredient_to_search);
                }
                else {
                    std::cout << "검색할 재료를 입력해주세요." << std::endl;
                }
            }
            else {
                std::cout << "잘못된 검색 옵션입니다." << std::endl;
            }

        }
        else if (choice == 4) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}