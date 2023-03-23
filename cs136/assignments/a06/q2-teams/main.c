/////////////////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT (v4)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement posted on edX:
// (Course > Assignments > Assignment Information & Policies > Academic Integrity Policy)
/////////////////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with:

// None
//
// Name: Oliver Tattersall
// login ID: omtatter
//////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <assert.h>
#include "cs136-trace.h"
#include "team.h"

//////////////////////////////////////////////////////////////////////////////////////////
// These definitions are used to control testing.
const int MAX_TEAMS = 4;

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE

// print_reason(r) prints information about the reason for a failure
//    as indicated in the structure r.
// requires: r is a valid pointer to a reason
//           The reason code is either FAIL_INSUFFICIENT_FUNDS or FAIL_ROSTER_FULL
// effects: produces output

void print_reason(const struct reason* const r) {
  assert(r);
  assert(r->code == FAIL_INSUFFICIENT_FUNDS || r->code == FAIL_ROSTER_FULL);
  if (r->code == FAIL_INSUFFICIENT_FUNDS) {
    printf("Team %d doesn't have enough money\n", r->team_num);
  } else if (r->code == FAIL_ROSTER_FULL) {
    printf("Team %d has a full roster\n", r->team_num);
  } 
}
// END OF DO NOT CHANGE REGION
//////////////////////////////////////////////////////////////////////////////////////////

// get_team_by_id(teamid, teams, len) returns a pointer to the team with id teamid, returns NULL if there is no team
// requires: teamid>=0, teams be non-NULL, len>0

struct team *get_team_by_id(int teamid, struct team teams[], int len){
  assert(teamid >= 0);
  assert(teams);
  assert(len>0);
  for(int i = 0; i < len; i++){
    if(teamid == (teams[i]).team_id){
      return teams+i;
    }
  }
  return NULL;
}

void do_io_tests(void) {
  const int MAKE = lookup_symbol("team");
  const int ADD = lookup_symbol("add_player");
  const int TRADE = lookup_symbol("trade_players");
  const int SELL = lookup_symbol("sell_player");
  const int IS_ON = lookup_symbol("is_on");
  const int PRINT = lookup_symbol("print");
  struct reason err = {0, TEAM_INVALID_ID};

  int num_teams = 0;
  struct team teams[4] = {}; // MUST BE = MAX_TEAMS
  for(int i = 0; i< MAX_TEAMS ;i++){
    team_init_empty(&(teams[i]));
    // teams[i] = team_empty;
  }

  while(1){
    int cmd = read_symbol();
    if(cmd==MAKE){
      int id = 0;
      int cash = 0;
      scanf("%d", &id);
      scanf("%d", &cash);

      if(num_teams==4){
        printf("Teams are all initialized\n");
      }else{
        // team_init_empty(teams+num_teams);
        team_setup(teams+num_teams, id, cash);
        num_teams+=1;
      }
    }else if(cmd == ADD){
      int teamid = 0;
      int playerid = 0;
      int value = 0;
      
      scanf("%d", &teamid);
      scanf("%d", &playerid);
      scanf("%d", &value);
      struct team *temp = get_team_by_id(teamid, teams, num_teams);
      
      bool success = team_add_player(temp, playerid, value, &err);
      if(!success){
        printf("add_player failed : ");
        print_reason(&err);
        // if(err.code == FAIL_ROSTER_FULL){
        //   printf("Team %d has a full roster\n", teamid);
        // }else{
        //   printf("Team %d doesn't have enough money\n", teamid);
        // }
      }
      
    }else if(cmd == TRADE){
      int teamid = 0;
      int playerid = 0;
      int team2id = 0;
      int player2id = 0;
      scanf("%d", &teamid);
      scanf("%d", &playerid);
      scanf("%d", &team2id);
      scanf("%d", &player2id);
      struct team *temp = get_team_by_id(teamid, teams, num_teams);
      struct team *temp2 = get_team_by_id(team2id, teams, num_teams);
      
      // team_print(&t2);
      // printf("%d\n", temp->team_id);
      // printf("%d\n", temp2->team_id);
      bool success = team_trade_players(temp, playerid, temp2, player2id, &err);
      // team_print(&t2);
      if(!success){
        printf("trade_players failed : Team %d doesn't have enough money\n", err.team_num);
        
      }
      
    }else if(cmd == SELL){
      int teamid = 0;
      int playerid = 0;
      int team2id = 0;
      
      scanf("%d", &teamid);
      scanf("%d", &playerid);
      scanf("%d", &team2id);
      struct team *temp = get_team_by_id(teamid, teams, num_teams);
      struct team *temp2 = get_team_by_id(team2id, teams, num_teams);
      
      bool success = team_sell_player(temp, playerid, temp2,  &err);
      if(!success){
        printf("sell_player failed : ");
        print_reason(&err);
        // if(err.code == FAIL_ROSTER_FULL){
        //   printf("Team %d has a full roster\n", err.team_num);
        // }else{
        //   printf("Team %d doesn't have enough money\n", err.team_num);
        // }
      }
    }else if(cmd == IS_ON){
      int teamid =0;
      int playerid = 0;
      
      scanf("%d", &teamid);
      scanf("%d", &playerid);
      struct team *temp = get_team_by_id(teamid, teams, num_teams);
      if(team_is_player_on(temp, playerid)){
          printf("Player %d is on team %d\n", playerid, teamid);
        }else{
          printf("Player %d is not on team %d\n", playerid, teamid);
        }
      
    }else if(cmd == PRINT){
      // printf("\n\nhello\n\n");
      int teamid = 0;
      scanf("%d", &teamid);
      struct team *temp = get_team_by_id(teamid, teams, num_teams);
      team_print(temp);
    }else{
      // team_print(&t1);
      break;
    }
    // team_print(&t1);
  }
  
  // Possible messages for team command (nothing is printed if successful)
  //   "Teams are all initialized\n"

  // Possible messages for is_on command
  //   "Player %d is on team %d\n"
  //   "Player %d is not on team %d\n"

  // Possible messages for add_player command (nothing is printed if successful)
  //   "add_player failed : " 
  //    followed by calling print_reason to print the reason for the failure

  // Possible messages for sell_player command (nothing is printed if successful)
  //   "sell_player failed : "
  //    followed by calling print_reason to print the reason for the failure

  // Possible messages for trade_players command (nothing is printed if successful)
  //   "trade_players failed : "
  //    followed by calling print_reason to print the reason for the failure

}

int main(void) {
  // DO NOT CHANGE THE CODE BELOW THIS LINE
  do_io_tests();
}
