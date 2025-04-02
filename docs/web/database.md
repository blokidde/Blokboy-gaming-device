# Database

## Database EERD

## Tables

### players

| Field       | Type        | Description                |
|-------------|-------------|----------------------------|
| player_id   | INT (PK)    | Unique player identifier   |
| created_at  | TIMESTAMP   | Timestamp of creation      |

### games

| Field       | Type        | Description                      |
|-------------|-------------|----------------------------------|
| game_id     | INT (PK)    | Unique game session ID           |
| player_id   | INT (FK)    | Links to player                  |
| start_time  | TIMESTAMP   | Game start time                  |

### scores

| Field        | Type        | Description             |
|--------------|-------------|-------------------------|
| score_id     | INT (PK)    | Unique score ID         |
| game_id      | INT (FK)    | Links to game           |
| score_value  | INT         | Score earned in game    |

### sensor_data

| Field         | Type         | Description                             |
|---------------|--------------|-----------------------------------------|
| sensor_id     | INT (PK)     | Unique sensor entry                     |
| game_id       | INT (FK)     | Links to game                           |
| direction     | VARCHAR(10)  | 'up', 'down', 'left', or 'right'        |
| total_moves   | INT          | Number of directional movements         |
| timestamp     | TIMESTAMP    | When this sensor data was recorded      |

## Relationships

- One `player` can have many `games`
- Each `game` has one `score`
- Each `game` can have many `sensor_data` entries

## Normalization

- The database is normalized to 3rd Normal Form (3NF).
- No redundant data across tables.
- All non-key attributes depend on the full primary key.
- Relationships are clean and maintainable.

## Sensor Data Flexibility

The current system gets four directional inputs from a joystick:
- up
- down
- left
- right

however it is fairly easy to add more sensor data to this table without modifying the schema.

### SQL implementations

```sql
INSERT INTO players (player_id, created_at) VALUES (1, NOW());
INSERT INTO games (game_id, player_id, start_time) VALUES (1, 1, NOW());
INSERT INTO scores (score_id, game_id, score_value) VALUES (1, 1, 45);
INSERT INTO sensor_data (sensor_id, game_id, direction, total_moves, timestamp) VALUES
(1, 1, 'up', 15, NOW()),
(2, 1, 'down', 10, NOW()),
(3, 1, 'left', 5, NOW()),
(4, 1, 'right', 20, NOW());
```
