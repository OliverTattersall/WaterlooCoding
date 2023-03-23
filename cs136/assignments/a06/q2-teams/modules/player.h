
// NOTE that a player is not valid (i.e., hasn't been assigned)
//    if the player_id is PLAYER_INVALID_ID (which is a negative value).
extern const int PLAYER_INVALID_ID;       // This is negative
extern const struct player player_empty;

struct player {
  int player_id;    // assume it is unique across all player and is >= 0
  int value;        // >= 0
};

// player_setup(p, id, val)
//    Setup the fields for the specified player
// requires: p is a valid player
//    id and val >= 0
void player_setup(struct player* const p, const int id, const int val);

// player_print(p) prints information about player p
// requires: p must be a valid player
void player_print(const struct player* const p);
