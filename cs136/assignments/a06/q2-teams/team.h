#include <stdbool.h>
#include "player.h"

// -----------------------------------------------------------------------
// Useful definitions
extern const int MAX_PLAYERS;        // NEW: Note this is 5
extern const int TEAM_INVALID_ID;    // Used for initialization.

// Reasons for failures
extern const int FAIL_INSUFFICIENT_FUNDS;
extern const int FAIL_ROSTER_FULL;

// Used to provide more information when some function calls fail
struct reason {
  int code;        // Success or failure (from above)
  int team_num;    // Which team had the problem
};

struct team {
  int team_id;
  int cash_available;         // how much money does the team have available
  int num_players;            // NEW: how many players are actually on the team
  struct player players[5];   // NEW: MUST BE = MAX_PLAYERS
};

extern const struct team team_empty;

//  ************************************************************************************
//  NOTES: Assume that all player ids are unique (you don't have to check for that).
//         Assume that all team ids are unique (you don't have to check).
//         A team must be initialized (using team_init_empty) before
//           being used in any other calls (you don't have to check for this).
//         Assume a team will only be "initialized" or "created" using team_setup once
//           (you do not have to check for this).
//  ************************************************************************************

// team_print(t) prints information about team t
//    NOTE: must print players from lowest player_id to highest player_id     
// requires: t is a valid pointer to a team with a valid team_id and
//           team_player_value(t) + team_cash(t) = team_value(t) 
// effects: prints output
void team_print(const struct team* const t);

// team_player_value(t) returns the sum of the value of all of the players
//     on team t
// requires: t is a valid pointer to a team with a valid team_id
int team_player_value(const struct team* const t);

// team_value(t) returns the total value of the team t
//     (i.e., the sum of the value of all of the players and the cash_available)
// requires: t is a valid pointer to a team with a valid team_id
int team_value(const struct team* const t);

// team_cash(t) returns the cash available for team t
// requires: t is a valid pointer to a team with a valid team_id
int team_cash(const struct team* const t);

// team_init_empty(t) 
//     Initialize team t to empty.
//       Team id should be set to TEAM_INVALID_ID and other fields
//       besides player structures should be zero.
//     All players must be initialized to player_empty.
// requires: t is a valid pointer to a team
// effects: modifies team t
void team_init_empty(struct team* const t);

// team_setup(t, id, cash) 
//     Setup (create) team t by assigning it a team id = id
//       and the initial amount of cash_available.
// requires: t is a valid pointer to a team with a team_id = TEAM_INVALID_ID
//           no players have been assigned to the team 
//           (i.e., player_id = PLAYER_INVALID_ID)
//           for all players on the team
//           id and cash >= 0
//           num_players = 0
// effects: modifies team t
void team_setup(struct team* const t, int id, int cash);

// team_get_id(t) returns the id that was assigned to team t
// requires: t is a valid pointer to a team
int team_get_id(const struct team* const t);

// team_is_player_on(t, id) returns true if the team has a player
//     with player id = id on the team.
//     Otherwise returns false.
// requires: t is a valid pointer to a team with a valid team_id
//     id >= 0
bool team_is_player_on(const struct team* const t, int id);

// team_add_player(t, id, val, r)
//     Attempt to add player with id and value (val) to team t
//     First, if the team has reached the maximum number of players the call
//        fails (and the reason is provided). 
//     Second if the team does not have
//        enough cash available to pay for the value of the player,
//        the call fails (and the reason is provided). 
//     On a failure, information about the failure is provided in reason r
//        before the call returns false.
//     If the player can be added the amount of cash available for the team
//        is decreased by the value (val) of the player
//        (i.e., they have to pay for the player).
//     If successful, the call returns true and the reason should be ignored.
// requires: t is a valid pointer to a team with a valid team_id
//     id and val >= 0
//     player with identity id is not already on the team
//     Reason r is a valid pointer.
// effects: may modify team t and reason r
bool team_add_player(struct team* const t, int id, int val,
     struct reason *r);

// team_sell_player(t1, id, t2, r) 
//     Team t1 attempts to sell the specified player (id) to team t2
//     First, if team t2 has reached the maximum number of players, the call
//        fails (and the reason is provided). 
//     Second if the team t2 does not have
//        enough cash available to pay for the value of the player,
//        the call fails (and the reason is provided). 
//     On a failure, information about the failure is provided in reason r
//        before the call returns false.
//     If successful, the call returns true and the reason should be ignored.
// requires: t1 and t2 are valid pointer to a team both with a valid team_id
//     The specified player (id) is on team t1.
//     The specified player (id) is not on team t2.
//     Reason r is a valid pointer.
//     id >= 0.
//     t1 != t2
// effects: may modify team t1 and t2 and reason r
bool team_sell_player(struct team* const t1, int id,
     struct team* const t2, struct reason* const r);

// team_trade_players(t) team t1 attempts to trade player with id1 to team t2
//     in exchange for the player with id2 on team t2
//     If team t1 or t2 do not have enough cash available to cover the difference
//        in value between the two players, the call fails.
//     On a failure, information about the failure is provided in reason r
//        before the call returns false.
//     If successful, the call returns true and the reason should be ignored.
// requires: t1 and t2 are valid pointer to a team both with a valid team_id
//     The specified player (id1) is on team t1.
//     The specified player (id2) is on team t2.
//     Reason r is a valid pointer.
//     id1 and id2 >= 0
//     t1 != t2
// effects: may modify team t1 and t2 and reason r
bool team_trade_players(struct team* const t1, int id1,
     struct team* const t2, int id2, struct reason* const r);

