# Database

## Database EERD
![ERD](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/erd.png)
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

## choice for keys and candidate keys
For each table, i considered natural keys vs surrogate keys. i chose auto-incremented integers (INT) as primary keys because:

- They are efficient
- Easy to reference in foreign keys

No candidate keys existed in the sensor_data table.(game_id, direction) were considered, but this would prevent several entries for the same direction.

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

## SQL implementations

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

## how to use database
use this script to create the database with tables
```sql
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Player`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Player` (
  `player_id` INT(11) NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(50) NULL DEFAULT NULL,
  `created_at` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP(),
  `generate` TINYINT(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`player_id`),
  UNIQUE INDEX `player_id_UNIQUE` (`player_id` ASC) VISIBLE)
ENGINE = InnoDB
AUTO_INCREMENT = 72;


-- -----------------------------------------------------
-- Table `mydb`.`CurrentGame`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`CurrentGame` (
  `game_id` INT(11) NOT NULL AUTO_INCREMENT,
  `player_id` INT(11) NOT NULL,
  `started_at` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP(),
  `ended_at` TIMESTAMP NULL DEFAULT NULL,
  PRIMARY KEY (`game_id`),
  INDEX `fk_currentgame_player_idx` (`player_id` ASC) VISIBLE,
  CONSTRAINT `fk_currentgame_player`
    FOREIGN KEY (`player_id`)
    REFERENCES `mydb`.`Player` (`player_id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
AUTO_INCREMENT = 73;


-- -----------------------------------------------------
-- Table `mydb`.`JoystickInput`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`JoystickInput` (
  `joystick_id` INT(11) NOT NULL AUTO_INCREMENT,
  `game_id` INT(11) NOT NULL,
  `totalup` INT(11) NOT NULL,
  `totaldown` INT(11) NOT NULL,
  `totalright` INT(11) NOT NULL,
  `totalleft` INT(11) NOT NULL,
  `created_at` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP(),
  PRIMARY KEY (`joystick_id`),
  INDEX `fk_joystick_game_idx` (`game_id` ASC) VISIBLE,
  CONSTRAINT `fk_joystickinput_game`
    FOREIGN KEY (`game_id`)
    REFERENCES `mydb`.`CurrentGame` (`game_id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
AUTO_INCREMENT = 58;


-- -----------------------------------------------------
-- Table `mydb`.`Score`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Score` (
  `score_id` INT(11) NOT NULL AUTO_INCREMENT,
  `game_id` INT(11) NOT NULL,
  `score_value` INT(11) NOT NULL,
  `created_at` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP(),
  PRIMARY KEY (`score_id`),
  INDEX `fk_score_game_idx` (`game_id` ASC) VISIBLE,
  CONSTRAINT `fk_score_game`
    FOREIGN KEY (`game_id`)
    REFERENCES `mydb`.`CurrentGame` (`game_id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
AUTO_INCREMENT = 58;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

```
