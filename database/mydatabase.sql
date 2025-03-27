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
