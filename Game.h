#ifndef GAME_H
#define GAME_H
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "Base.h"
#include "Notice.h"
#include "View.h"
class Game: public Base, public Notice, public View {
 struct BattleOptions {
   int user, computer, win_result;
 };

 int game_level;
 bool exit_game;
 std::vector<BattleOptions> battleRules;



 public: 
 Game(std::string t = ""){
  title = t;
  initialzeBattleRules();
 }

 BattleOptions rule(int user, int computer, int win_result){
  BattleOptions option;
  option.user = user;
  option.computer = computer;
  option.win_result = win_result;

  return option;
 }

 void initialzeBattleRules(){

  /*
  user win
  User Computer
  1     3 
  2     1
  3     2

  computer win
  User Computer
  1     2 
  2     3
  3     1

  {
   user: 1,
   computer: 3,
   win_result: 1
  }
 */

  // user win
  battleRules.push_back(rule(1, 3, 1));
  battleRules.push_back(rule(2, 1, 1));
  battleRules.push_back(rule(3, 2, 1));

  // computer win
  battleRules.push_back(rule(1, 2, 2));
  battleRules.push_back(rule(2, 3, 2));
  battleRules.push_back(rule(3, 1, 2));
 }

 

 int main(){
  call();

  return 0;
 }

 void call(){
   do {
    system("clear");

    std::cout << displayTitle();
    std::cout << displayMenu();

    getUserInput();

    switch (game_level)
    {
    case 1:
      easyLevel();
      break;
    case 2:
      mediumLevel();
      break;
    case 3:
      hardLevel();
      break;
    case 4:
      settings();
      break;
    case 5:
      exit_game = true;
      setSuccessNotice("\n\tThank you for using the game. Bye!");
      break;
    default:
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      setErrorNotice("\n\tInvalid Input.");
      break;
    }

    if(hasNotice()){
      std::cout << displayNotice();
      resetNotice();
    }
      

   } while(!exit_game);
 }

 void easyLevel(){
  int user_battle_option, computer_battle_option;
  std::string battle_options[3] = {"Paper", "Scissors", "Rock"};
  // 1 - Paper, 2 - Scissors, 3 - Rock
  std::cout << displayBattleOptions();
  std::cout << "\n\tEnter your Battle Option Number: ";
  std::cin >> user_battle_option;
  
  // Seed the random number generator
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

 computer_battle_option = (std::rand() % 3) + 1;


 std::cout << "\n\tUser choose: " << battle_options[user_battle_option-1];
 std::cout << "\n\tComputer choose: " << battle_options[computer_battle_option-1];
 
 int battle_result = battle(user_battle_option, computer_battle_option);

 std::cout << std::endl << displayBattleResult(battle_result);

 }

 int battle(int user_battle_option, int computer_battle_option){
  if(user_battle_option == computer_battle_option)
   return 0;

  for(int i = 0; i < battleRules.size(); i++){
   if(battleRules[i].user == user_battle_option && battleRules[i].computer == computer_battle_option)
    return battleRules[i].win_result;
  }
  
  // 0 - tie
  // 1 - user wins
  // 2 - computer wins

  return 0;
 }

 std::string displayBattleResult(int win_result){
  std::string battle_result = "";

  switch (win_result)
  {
  case 0:
   battle_result = ANSI_COLOR_ORANGE + std::string("\n\tI'ts A Tie.") + ANSI_COLOR_RESET;
   break;
  case 1:
   battle_result = ANSI_COLOR_GREEN + std::string("\n\tYou Win.") + ANSI_COLOR_RESET;
   break;
  case 2:
   battle_result = ANSI_COLOR_RED + std::string("\n\tComputer Wins.") + ANSI_COLOR_RESET;
   break;
  }

  return battle_result;
 }



 void mediumLevel(){
  std::cout << "Medium";
 }

 void hardLevel(){
  std::cout << "Hard";
 }

 void settings(){
  std::cout << "Settings";
 }

 void getUserInput(){
  std::cout << "\tSelect the level of difficulty: ";
  std::cin >> game_level;
 }

 std::string displayMenu(){
  // + concatenation is used to fix ANSI_COLOR_BLUE + std::string("\tMain Menu\n") 
  return ANSI_COLOR_CYAN + std::string("\tLevel of Difficulty\n") +
   "\t1. Easy\n"
   "\t2. Medium\n"
   "\t3. Hard\n"
   "\t4. Settings\n"
   "\t5. Exit\n\n" + ANSI_COLOR_RESET;
 }

 std::string displayBattleOptions(){
  return ANSI_COLOR_CYAN + std::string("\tList of Battle Options\n") +
   "\t1. Paper(papel)\n"
   "\t2. Scissors(gunting)\n"
   "\t3. Rock(bato)\n"
   "\t4. Back\n" + ANSI_COLOR_RESET;
 }
};
#endif