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
