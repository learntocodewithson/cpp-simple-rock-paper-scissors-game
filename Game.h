#ifndef GAME_H
#define GAME_H
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "Base.h"
#include "Notice.h"
#include "View.h"
class Game: public Base, public View {
 struct BattleOptions {
   int user, computer, win_result;
   std::string battle_rule;
 };

 int game_level, user_win_count, computer_win_count, round_counter;
 bool exit_game;
 std::vector<BattleOptions> battleRules;

 public: 
 Game(std::string t = ""){
  title = t;
  user_win_count = computer_win_count = round_counter = 0;
  initialzeBattleRules();
 }

 BattleOptions rule(int user, int computer, int win_result, std::string battle_rule){
  BattleOptions option;
  option.user = user;
  option.computer = computer;
  option.win_result = win_result;
  option.battle_rule = battle_rule;

  return option;
 }

 void initialzeBattleRules(){

  /*
  user win
  User         Computer
  1(paper)      3 
  2(scissors)   1
  3(rock)       2

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
  battleRules.push_back(rule(1, 3, 1, "Paper covers Rock"));
  battleRules.push_back(rule(2, 1, 1, "Scissors cuts Paper"));
  battleRules.push_back(rule(3, 2, 1, "Rock crushes Scissors"));

  // computer win
  battleRules.push_back(rule(1, 2, 2, "Scissors cuts Paper"));
  battleRules.push_back(rule(2, 3, 2, "Rock crushes Scissors"));
  battleRules.push_back(rule(3, 1, 2, "Paper covers Rock"));
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

 void battleNow(int win_limit, std::string level){
  std::cout << ANSI_COLOR_ORANGE << "\n\tYou choose " << level << " level. Whoever got " << win_limit << " wins first, will be the winner." << ANSI_COLOR_RESET;
  
  do {
    round_counter++; // start to round 1
    startTheGame(win_limit);
  } while(user_win_count != win_limit && computer_win_count != win_limit);

  std::cout << ANSI_COLOR_GREEN << "\n\n\tUser Win: " << user_win_count << ANSI_COLOR_RESET;
  std::cout << ANSI_COLOR_RED << "\n\tComputer Win: " << computer_win_count << std::endl << ANSI_COLOR_RESET;

  if(user_win_count == win_limit){
    setSuccessNotice("\n\tCongratulations, You Win!");
  } else {
    setErrorNotice("\n\tComputer Wins!, Better luck next time! :)");
  }

  resetUserComputerWinningScores();
 }

 void resetUserComputerWinningScores(){
  user_win_count = computer_win_count = round_counter= 0;
 }

 void startTheGame(int win_limit){
  int user_battle_option, computer_battle_option;
  bool validBattleOption = false;
  std::string battle_options[3] = {"Paper", "Scissors", "Rock"};
  // 1 - Paper, 2 - Scissors, 3 - Rock
  std::cout << displayBattleOptions();
  std::cout << ANSI_COLOR_ORANGE << "\n\tRound " << round_counter << ANSI_COLOR_RESET;

  do {
    
    if(hasNotice())
      std::cout << displayNotice();

    std::cout << "\n\tEnter your Battle Option Number: ";
     if (!(std::cin >> user_battle_option)) {
      resetUserScanInput("\n\tInvalid Battle Option");
     }else{
      
       std::vector<int> battleOptionRange;
       battleOptionRange.push_back(1);
       battleOptionRange.push_back(2);
       battleOptionRange.push_back(3);

       if(!validateIfOutOfRange(battleOptionRange, user_battle_option)){
        // start
          validBattleOption = true;
          resetNotice();

          // Seed the random number generator
          std::srand(static_cast<unsigned int>(std::time(nullptr)));

          computer_battle_option = (std::rand() % 3) + 1;

          std::cout << "\n\tYou choose: " << ANSI_COLOR_MAGENTA << battle_options[user_battle_option-1] << ANSI_COLOR_RESET;
          std::cout << "\n\tComputer choose: " << ANSI_COLOR_MAGENTA << battle_options[computer_battle_option-1] << ANSI_COLOR_RESET;
          
          int battle_result = battle(user_battle_option, computer_battle_option);
          std::string battle_rule = battleRule(user_battle_option, computer_battle_option);

          if(battle_rule != ""){
            toUpperCase(battle_rule);
            
            std::cout << "\n\n\t" << displayLine() << "\n\t";
            
            if(battle_result == 1){
              std::cout << ANSI_COLOR_GREEN;
            }else if(battle_result == 2){
              std::cout << ANSI_COLOR_RED;
            }
            std::cout << battle_rule << ANSI_COLOR_RESET << "\n\t" <<  displayLine();
          }
            
          
          // increment user or computer winning count
          processWinningCount(battle_result);
          
          if(user_win_count != win_limit && computer_win_count != win_limit){
            std::cout << std::endl << displayBattleResult(battle_result);
          }
        // end
       } else {
        resetUserScanInput("\n\tInvalid Battle Option");
       }
      
     }

  } while(!validBattleOption);

 }

 bool validateIfOutOfRange(std::vector<int> rangeOfNumbers, int user_input){
  for (int i = 0; i < rangeOfNumbers.size(); ++i){
    if(rangeOfNumbers[i] == user_input)
     return false;
  }
  
  return true;
 }

 void processWinningCount(int battle_result){
  if(battle_result == 1){
    user_win_count++;
  }else if(battle_result == 2){
    computer_win_count++;
  }
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

 std::string battleRule(int user_battle_option, int computer_battle_option){
  if(user_battle_option == computer_battle_option)
   return "";

  for(int i = 0; i < battleRules.size(); i++){
   if(battleRules[i].user == user_battle_option && battleRules[i].computer == computer_battle_option)
    return battleRules[i].battle_rule;
  }

  return "";
 }

 std::string displayBattleResult(int win_result){
  std::string battle_result = "";

  std::cout << ANSI_COLOR_GREEN << "\n\tUser Win: " << user_win_count << ANSI_COLOR_RESET;
  std::cout << ANSI_COLOR_RED << "\n\tComputer Win: " << computer_win_count << std::endl << ANSI_COLOR_RESET;
  
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

 void easyLevel(){
  battleNow(3, "easy");
 }

 void mediumLevel(){
  battleNow(7, "medium");
 }

 void hardLevel(){
  battleNow(10, "hard");
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
  return ANSI_COLOR_CYAN + std::string("\n\n\tList of Battle Options\n") +
   "\t1. Paper(papel)\n"
   "\t2. Scissors(gunting)\n"
   "\t3. Rock(bato)\n" + ANSI_COLOR_RESET;
 }
};
#endif