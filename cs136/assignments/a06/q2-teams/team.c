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
#include <stdbool.h>
#include "team.h"

// -----------------------------------------------------------------------
// DO NOT CHANGE THIS REGION OF CODE
const int MAX_PLAYERS = 5;
const int TEAM_INVALID_ID = -1;
const struct team team_empty = {TEAM_INVALID_ID, 0}; // Doesn't set players to empty_player
                                                     // Must be done by team_init_empty

// DO NOT CHANGE THESE
// Reasons for failures
const int FAIL_INSUFFICIENT_FUNDS = -1;
const int FAIL_ROSTER_FULL = -2;
// END OF DO NOT CHANGE REGION

// valid_team_pointer(t) takes a pointer to a team t and return true if it 
//                       is non-NULL and has a valid team id
static bool valid_team_pointer(const struct team * const t){
  return t!=NULL && t->team_id!=TEAM_INVALID_ID;
};


// YOU MUST COMPLETE THIS FUNCTION

// team_print(t) prints the team t, with players ordered by their id
// requires: t is a valid pointer to a team with a valid team_id
// effects: produces output
void team_print(const struct team* const t) {
  assert(valid_team_pointer(t));
  assert(team_player_value(t) + team_cash(t) == team_value(t));
  printf("Team %d : ", team_get_id(t));

  // int minid[5] = {-1,-1,-1,-1,-1}; // MAX PLAYERS = 5

  struct player players[5] = {};
  for(int i = 0; i < t->num_players; i++){
    players[i] = (t->players[i]);
  }
  

  for(int i = 0; i < t->num_players; i++){
    struct player *temp_min = &(players[i]);
    for(int j = i; j < t->num_players; j++){
      if(players[j].player_id < temp_min->player_id){
        temp_min = &(players[j]);
      
      }
    }
    struct player tempswap = players[i];
    players[i] = *temp_min;
    *temp_min = tempswap;
  }

  for(int i = 0; i < t->num_players; i++){
    player_print(&(players[i]));
  }

  // INSERT CODE HERE FOR PRINTING PLAYERS
  // Players must be printed from the lowest player_id to highest player_id.
  // You must NOT print players with player_id == PLAYER_INVALID_ID
  // The function you use to print the player is 
  //    player_print(player_ptr);  See player.h
  // player_print will take care of proper spacing.
  // See team_print in team.c of A5 if you need a better idea of what to do.

  printf("player value = %d cash = %d", team_player_value(t), team_cash(t));
  printf("\n");
}
// -----------------------------------------------------------------------





int team_player_value(const struct team* const t) {
  assert(valid_team_pointer(t));
  // Replace this with your code
  int sum = 0;

  for(int i = 0; i<t->num_players; i++){
    sum += t->players[i].value;
  }

  return sum;
}

int team_value(const struct team* const t) {
  assert(valid_team_pointer(t));
  return team_player_value(t)+t->cash_available;
  // Replace this with your code
  // return 0;
}

int team_cash(const struct team* const t) {
  assert(valid_team_pointer(t));
  // Replace this with your code
  return t->cash_available; 
}

void team_init_empty(struct team* const t) {
  // Replace this with your code
  assert(t);
  t->cash_available=0;
  t->team_id = TEAM_INVALID_ID;
  t->num_players=0;
  for(int i = 0; i < 5; i++){
    t->players[i] = player_empty;
  }

}

void team_setup(struct team* const t, const int id, const int cash) {
  assert(t);
  assert(t->team_id==TEAM_INVALID_ID);
  assert(id>=0);
  assert(cash >= 0);
  assert(t->num_players == 0);
  for(int i = 0; i<MAX_PLAYERS; i++){
    assert(t->players[i].player_id==PLAYER_INVALID_ID);
  }

  
  t->team_id = id;
  t->cash_available = cash;
  // Replace this with your code
}

int team_get_id(const struct team* const t) {
  assert(t);
  // Replace this with your code
  return t->team_id;
}

bool team_is_player_on(const struct team* const t, const int id) {
  assert(valid_team_pointer(t));
  assert(id>=0);
  
  // Replace this with your code
  for(int i = 0; i < t->num_players; i++){
    if(t->players[i].player_id==id){
      return true;
    }
  }
  return false;
}

// find_player(t, id) returns a pointer to the player with player_id id, returns NULL otherwise
// requires: t be non-NULL, id>=0
static struct player *find_player(struct team * const t, const int id){
  assert(id>=0);
  assert(t);
  for(int i = 0; i < t->num_players; i++){
    if(t->players[i].player_id==id){
      return &(t->players[i]);
    }
  }
  
  return NULL;

}


// balance_team(t) balances the team so all valid players are at the beginning of the players array
// requires: t be non-NULL
// effects: modifies t
static void balance_team(struct team * const t){
  assert(t);

  for(int i = 0; i < MAX_PLAYERS-1; i++){
    if(t->players[i].player_id==PLAYER_INVALID_ID){
      struct player temp = t->players[i];
      t->players[i] = t->players[i+1];
      t->players[i+1] = temp;
    }
  }

}


bool team_add_player(struct team* const t, const int id, const int val,
   struct reason *r) {
  assert(valid_team_pointer(t));
  assert(id>=0);
  assert(val >= 0);
  assert(r);
  for(int i = 0; i<t->num_players; i++){
    assert(t->players[i].player_id != id);
  }
  // Replace this with your code
  if(t->num_players==5){
    r->code = FAIL_ROSTER_FULL;
    r->team_num = t->team_id;
    return false;
  }

  if(t->cash_available<val){
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t->team_id;
    return false;
  }

  t->players[t->num_players].player_id =id;
  t->players[t->num_players].value =val;
  t->num_players+=1;
  t->cash_available-=val;

  return true;
}



bool team_sell_player(struct team* const t1, const int id,
     struct team* const t2, struct reason *r) {
  assert(valid_team_pointer(t1));
  assert(valid_team_pointer(t2));
  assert(r);
  assert(t1!=t2);
  assert(id>=0);
  assert(team_is_player_on(t1, id));
  assert(!team_is_player_on(t2, id));

  // Replace this with your code
  // if(t2->num_players==5){
  //   r->code = FAIL_ROSTER_FULL;
  //   r->code = t2->team_id;
  //   return false;
  // }

  struct player *temp = find_player(t1, id);

  // if(t2->cash_available <= temp->value){
  //   r->code = FAIL_INSUFFICIENT_FUNDS;
  //   r->team_num = t2->team_id;
  //   return false;
  // }

  bool success = team_add_player(t2, temp->player_id, temp->value, r);
  if(!success){
    return false;
  }
  
  t1->cash_available+=temp->value;

  *temp = player_empty;

  t1->num_players-=1;
  
  balance_team(t1);

  return true;
}

bool team_trade_players(struct team* const t1, const int id1,
     struct team* const t2, const int id2, struct reason *r) {
  // Replace this with your code
  assert(valid_team_pointer(t1));
  assert(valid_team_pointer(t2));
  assert(r);
  assert(t1!=t2);
  assert(id1>=0);
  assert(id2>=0);
  assert(team_is_player_on(t1, id1));
  assert(team_is_player_on(t2, id2));


  struct player *temp1 = find_player(t1, id1);
  struct player *temp2 = find_player(t2, id2);

  int diff = temp1->value - temp2->value;
  if(t1->cash_available + diff < 0){
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t1->team_id;
    return false;
  }else if(t2->cash_available - diff < 0){
    r->code = FAIL_INSUFFICIENT_FUNDS;
    r->team_num = t2->team_id;
    return false;
  }

  struct player temp3 = *temp1;
  *temp1 = *temp2;
  *temp2 = temp3;

  t1->cash_available += diff;
  t2->cash_available -= diff;


  return true;
}

