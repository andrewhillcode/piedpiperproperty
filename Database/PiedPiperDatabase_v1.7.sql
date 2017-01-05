-- MySQL dump 10.13  Distrib 5.6.23, for Win32 (x86)
--
-- Host: 127.0.0.1    Database: ifb299
-- ------------------------------------------------------
-- Server version	5.6.24-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `administrators`
--

DROP TABLE IF EXISTS `administrators`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `administrators` (
  `admin_id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(45) NOT NULL,
  PRIMARY KEY (`admin_id`),
  UNIQUE KEY `admin_id_UNIQUE` (`admin_id`),
  UNIQUE KEY `email_UNIQUE` (`email`),
  CONSTRAINT `admin_email` FOREIGN KEY (`email`) REFERENCES `user_information` (`email`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `administrators`
--

LOCK TABLES `administrators` WRITE;
/*!40000 ALTER TABLE `administrators` DISABLE KEYS */;
INSERT INTO `administrators` VALUES (1,'david@piedpiper.com');
/*!40000 ALTER TABLE `administrators` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contract_information`
--

DROP TABLE IF EXISTS `contract_information`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `contract_information` (
  `contract_id` int(11) NOT NULL,
  `start_date` date NOT NULL,
  `end_date` date NOT NULL,
  `price` int(11) NOT NULL,
  `description` varchar(500) NOT NULL,
  `terms` varchar(500) NOT NULL,
  `inclusions` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`contract_id`),
  UNIQUE KEY `contract_id_UNIQUE` (`contract_id`),
  CONSTRAINT `contract_information_contract_id` FOREIGN KEY (`contract_id`) REFERENCES `contracts` (`contract_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contract_information`
--

LOCK TABLES `contract_information` WRITE;
/*!40000 ALTER TABLE `contract_information` DISABLE KEYS */;
/*!40000 ALTER TABLE `contract_information` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contracts`
--

DROP TABLE IF EXISTS `contracts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `contracts` (
  `contract_id` int(11) NOT NULL AUTO_INCREMENT,
  `staff_id` int(11) NOT NULL,
  `tenant_id` int(11) NOT NULL,
  PRIMARY KEY (`contract_id`),
  UNIQUE KEY `contract_id_UNIQUE` (`contract_id`),
  KEY `contracts_staff_id_idx` (`staff_id`),
  KEY `contracts_tenant_id_idx` (`tenant_id`),
  CONSTRAINT `contracts_staff_id` FOREIGN KEY (`staff_id`) REFERENCES `staff_members` (`staff_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `contracts_tenant_id` FOREIGN KEY (`tenant_id`) REFERENCES `tenants` (`tenant_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contracts`
--

LOCK TABLES `contracts` WRITE;
/*!40000 ALTER TABLE `contracts` DISABLE KEYS */;
/*!40000 ALTER TABLE `contracts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `favourites`
--

DROP TABLE IF EXISTS `favourites`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `favourites` (
  `tenant_id` int(11) DEFAULT NULL,
  `house_id` int(11) DEFAULT NULL,
  `favourite_id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`favourite_id`),
  KEY `favourites_house_id_idx` (`house_id`),
  KEY `favourites_tenant_id` (`tenant_id`),
  CONSTRAINT `favourites_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `favourites_tenant_id` FOREIGN KEY (`tenant_id`) REFERENCES `tenants` (`tenant_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=43 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `favourites`
--

LOCK TABLES `favourites` WRITE;
/*!40000 ALTER TABLE `favourites` DISABLE KEYS */;
INSERT INTO `favourites` VALUES (3,1,4),(NULL,NULL,31),(NULL,NULL,32),(NULL,NULL,33),(NULL,1,34),(NULL,1,35),(NULL,1,36),(NULL,3,37),(NULL,3,38),(NULL,NULL,39),(2,1,40),(2,3,41),(2,5,42);
/*!40000 ALTER TABLE `favourites` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `house_images`
--

DROP TABLE IF EXISTS `house_images`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `house_images` (
  `image_id` int(11) NOT NULL AUTO_INCREMENT,
  `house_id` int(11) NOT NULL,
  `image_path` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`image_id`),
  UNIQUE KEY `house_image_id_UNIQUE` (`image_id`),
  KEY `house_images_house_id_idx` (`house_id`),
  CONSTRAINT `house_images_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `house_images`
--

LOCK TABLES `house_images` WRITE;
/*!40000 ALTER TABLE `house_images` DISABLE KEYS */;
INSERT INTO `house_images` VALUES (1,1,'prop1.jpg'),(2,1,'prop2.jpg'),(3,1,'prop3.jpg'),(4,1,'prop4.jpg'),(5,1,'prop5.jpg'),(6,1,'prop6.jpg'),(7,2,'prop7.jpg'),(8,2,'prop8.jpg'),(9,3,'prop9.jpg'),(10,4,'prop10.jpg'),(11,4,'prop11.jpg'),(12,4,'prop12.jpg'),(13,4,'prop13.jpg'),(14,5,'prop14.jpg'),(15,5,'prop15.jpg'),(16,5,'prop16.jpg'),(17,5,'prop17.jpg'),(18,6,'prop18.jpg');
/*!40000 ALTER TABLE `house_images` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `house_information`
--

DROP TABLE IF EXISTS `house_information`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `house_information` (
  `house_id` int(11) NOT NULL,
  `address` varchar(45) NOT NULL,
  `bed_number` int(11) NOT NULL,
  `bath_number` int(11) NOT NULL,
  `carport_number` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `overall_rating` int(11) DEFAULT NULL,
  `date_listed` date NOT NULL,
  `house_description` varchar(500) DEFAULT NULL,
  `furnished` int(11) NOT NULL,
  `type` varchar(500) DEFAULT NULL,
  `available` int(1) NOT NULL,
  `longitude` float DEFAULT NULL,
  `latitude` float DEFAULT NULL,
  PRIMARY KEY (`house_id`),
  UNIQUE KEY `house_id_UNIQUE` (`house_id`),
  UNIQUE KEY `address_UNIQUE` (`address`),
  CONSTRAINT `house_information_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `house_information`
--

LOCK TABLES `house_information` WRITE;
/*!40000 ALTER TABLE `house_information` DISABLE KEYS */;
INSERT INTO `house_information` VALUES (1,'123 Fake Street',3,2,2,200,NULL,'2015-09-03','This is a house that has a door and a few rooms and stuff like that',1,'House',1,-27.683,152.942),(2,'82 Hello Drive',4,3,2,535,NULL,'2015-09-03','This house is super cool!',0,'House',1,-27.358,153.132),(3,'15 Micko Street',6,6,6,1250,NULL,'2015-09-03','Who could ever want a better house?',1,'House',1,-27.373,153.106),(4,'27 Lower Drive',2,2,2,190,NULL,'2015-09-03','This is a small hosue',1,'House',1,-27.572,152.936),(5,'32 Franklin Street',3,2,2,220,NULL,'2015-09-03','A house for people who drink Mount Franklin',0,'House',1,-27.437,153.116),(6,'77 NotAvailable Road',8,1,1,666,NULL,'2015-10-03','This house is currently being rented and is hidden.',1,'Apartment',0,-27.531,153.013);
/*!40000 ALTER TABLE `house_information` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `houses`
--

DROP TABLE IF EXISTS `houses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `houses` (
  `house_id` int(11) NOT NULL AUTO_INCREMENT,
  `staff_id` int(11) DEFAULT NULL,
  `owner_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`house_id`),
  UNIQUE KEY `house_id_UNIQUE` (`house_id`),
  KEY `house_staff_id_idx` (`staff_id`),
  KEY `house_owner_id_idx` (`owner_id`),
  CONSTRAINT `house_owner_id` FOREIGN KEY (`owner_id`) REFERENCES `owners` (`owner_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `house_staff_id` FOREIGN KEY (`staff_id`) REFERENCES `staff_members` (`staff_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `houses`
--

LOCK TABLES `houses` WRITE;
/*!40000 ALTER TABLE `houses` DISABLE KEYS */;
INSERT INTO `houses` VALUES (1,1,1),(2,2,2),(3,2,1),(4,1,2),(5,1,2),(6,2,2);
/*!40000 ALTER TABLE `houses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `incidents`
--

DROP TABLE IF EXISTS `incidents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `incidents` (
  `incident_id` int(11) NOT NULL AUTO_INCREMENT,
  `tenant_id` int(11) NOT NULL,
  `house_id` int(11) NOT NULL,
  `details` varchar(500) NOT NULL,
  `pictures` varchar(1000) DEFAULT NULL,
  `date` date NOT NULL,
  PRIMARY KEY (`incident_id`),
  UNIQUE KEY `incident_id_UNIQUE` (`incident_id`),
  KEY `incidents_tenant_id_idx` (`tenant_id`),
  KEY `incidents_house_id_idx` (`house_id`),
  CONSTRAINT `incidents_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `incidents_tenant_id` FOREIGN KEY (`tenant_id`) REFERENCES `tenants` (`tenant_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `incidents`
--

LOCK TABLES `incidents` WRITE;
/*!40000 ALTER TABLE `incidents` DISABLE KEYS */;
/*!40000 ALTER TABLE `incidents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inspections`
--

DROP TABLE IF EXISTS `inspections`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `inspections` (
  `inspection_id` int(11) NOT NULL AUTO_INCREMENT,
  `staff_id` int(11) NOT NULL,
  `house_id` int(11) NOT NULL,
  `details` varchar(500) DEFAULT NULL,
  `date` date DEFAULT NULL,
  PRIMARY KEY (`inspection_id`),
  UNIQUE KEY `inspection_id_UNIQUE` (`inspection_id`),
  KEY `inspections_staff_id_idx` (`staff_id`),
  KEY `inspections_house_id_idx` (`house_id`),
  CONSTRAINT `inspections_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `inspections_staff_id` FOREIGN KEY (`staff_id`) REFERENCES `staff_members` (`staff_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inspections`
--

LOCK TABLES `inspections` WRITE;
/*!40000 ALTER TABLE `inspections` DISABLE KEYS */;
/*!40000 ALTER TABLE `inspections` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `owners`
--

DROP TABLE IF EXISTS `owners`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `owners` (
  `owner_id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(45) NOT NULL,
  PRIMARY KEY (`owner_id`),
  UNIQUE KEY `owner_id_UNIQUE` (`owner_id`),
  UNIQUE KEY `email_UNIQUE` (`email`),
  CONSTRAINT `owner_email` FOREIGN KEY (`email`) REFERENCES `user_information` (`email`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `owners`
--

LOCK TABLES `owners` WRITE;
/*!40000 ALTER TABLE `owners` DISABLE KEYS */;
INSERT INTO `owners` VALUES (2,'alan@hili.com'),(1,'roger.wilson@wilson.com');
/*!40000 ALTER TABLE `owners` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `renting_tenants`
--

DROP TABLE IF EXISTS `renting_tenants`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `renting_tenants` (
  `house_id` int(11) NOT NULL,
  `tenant_id` int(11) NOT NULL,
  PRIMARY KEY (`house_id`,`tenant_id`),
  UNIQUE KEY `tenant_id_UNIQUE` (`tenant_id`),
  CONSTRAINT `renting_tenants_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `renting_tenants_tenant_id` FOREIGN KEY (`tenant_id`) REFERENCES `tenants` (`tenant_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `renting_tenants`
--

LOCK TABLES `renting_tenants` WRITE;
/*!40000 ALTER TABLE `renting_tenants` DISABLE KEYS */;
INSERT INTO `renting_tenants` VALUES (1,3),(1,4),(1,5);
/*!40000 ALTER TABLE `renting_tenants` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reviews`
--

DROP TABLE IF EXISTS `reviews`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reviews` (
  `tenant_id` int(11) NOT NULL,
  `house_id` int(11) NOT NULL,
  `rating` int(11) DEFAULT NULL,
  `description` varchar(500) DEFAULT NULL,
  `date` date DEFAULT NULL,
  PRIMARY KEY (`tenant_id`,`house_id`),
  UNIQUE KEY `tenant_id_UNIQUE` (`tenant_id`),
  KEY `reviews_house_id_idx` (`house_id`),
  CONSTRAINT `reviews_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `reviews_tenant_id` FOREIGN KEY (`tenant_id`) REFERENCES `tenants` (`tenant_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reviews`
--

LOCK TABLES `reviews` WRITE;
/*!40000 ALTER TABLE `reviews` DISABLE KEYS */;
/*!40000 ALTER TABLE `reviews` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `staff_members`
--

DROP TABLE IF EXISTS `staff_members`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `staff_members` (
  `staff_id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(45) NOT NULL,
  `biography` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`staff_id`),
  UNIQUE KEY `staff_id_UNIQUE` (`staff_id`),
  UNIQUE KEY `email_UNIQUE` (`email`),
  CONSTRAINT `staff_email` FOREIGN KEY (`email`) REFERENCES `user_information` (`email`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `staff_members`
--

LOCK TABLES `staff_members` WRITE;
/*!40000 ALTER TABLE `staff_members` DISABLE KEYS */;
INSERT INTO `staff_members` VALUES (1,'blake@piedpiper.com','I have been working here for two days now and am really enjoying it!'),(2,'kelly@piedpiper.com','Hi my name is Kelly Holden and this is my favourite site on the internet!');
/*!40000 ALTER TABLE `staff_members` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tenants`
--

DROP TABLE IF EXISTS `tenants`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tenants` (
  `tenant_id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(45) NOT NULL,
  `DOB` date DEFAULT NULL,
  PRIMARY KEY (`tenant_id`),
  UNIQUE KEY `tenant_id_UNIQUE` (`tenant_id`),
  UNIQUE KEY `email_UNIQUE` (`email`),
  CONSTRAINT `tenant_email` FOREIGN KEY (`email`) REFERENCES `user_information` (`email`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tenants`
--

LOCK TABLES `tenants` WRITE;
/*!40000 ALTER TABLE `tenants` DISABLE KEYS */;
INSERT INTO `tenants` VALUES (1,'m.j.lee@hotmail.com','1993-08-11'),(2,'john.smith@test.com','1980-01-01'),(3,'diane.jones@gmail.com','1985-02-18'),(4,'pamela.gray@gmail.com','1990-05-21'),(5,'ryan.simmons@gmail.com','1991-05-10');
/*!40000 ALTER TABLE `tenants` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `testamonies`
--

DROP TABLE IF EXISTS `testamonies`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `testamonies` (
  `tenant_id` int(11) NOT NULL,
  `rating` int(11) NOT NULL,
  `description` varchar(500) DEFAULT NULL,
  `date` date DEFAULT NULL,
  PRIMARY KEY (`tenant_id`),
  UNIQUE KEY `tenant_id_UNIQUE` (`tenant_id`),
  CONSTRAINT `testamonies_tenant_id` FOREIGN KEY (`tenant_id`) REFERENCES `tenants` (`tenant_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `testamonies`
--

LOCK TABLES `testamonies` WRITE;
/*!40000 ALTER TABLE `testamonies` DISABLE KEYS */;
INSERT INTO `testamonies` VALUES (1,5,'Great staff and great website, I could not be happier renting from you!!','2015-04-04');
/*!40000 ALTER TABLE `testamonies` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_information`
--

DROP TABLE IF EXISTS `user_information`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_information` (
  `email` varchar(45) NOT NULL,
  `first_name` varchar(45) NOT NULL,
  `last_name` varchar(45) DEFAULT NULL,
  `contact_number` int(11) DEFAULT NULL,
  `profile_picture` varchar(250) DEFAULT NULL,
  `password` varchar(45) NOT NULL,
  `date_joined` date DEFAULT NULL,
  PRIMARY KEY (`email`),
  UNIQUE KEY `email_UNIQUE` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_information`
--

LOCK TABLES `user_information` WRITE;
/*!40000 ALTER TABLE `user_information` DISABLE KEYS */;
INSERT INTO `user_information` VALUES ('alan@hili.com','Alan','Hili',443218765,NULL,'password','2015-10-01'),('andrew@piedpiper.com','Andrew','Hill',478078375,NULL,'pass','2015-09-30'),('blake@piedpiper.com','Blake','Sully',412558461,'','password','2015-09-01'),('david@piedpiper.com','David','Piper',412345678,'','password','2015-08-31'),('diane.jones@gmail.com','Diane','Jones',412589541,'','password','2015-09-04'),('john.smith@test.com','John','Smith',447125489,'','password','2015-09-04'),('kelly@piedpiper.com','Kelly','Holden',415784259,'img/profiles/kellyHolden.jpg','password','2015-09-04'),('m.j.lee@hotmail.com','Michael','Lee',435088532,'','password','2015-09-04'),('pamela.gray@gmail.com','Pamela','Gray',457812014,'','password','2015-09-04'),('roger.wilson@wilson.com','Roger','Wilson',453985120,'','password','2015-09-02'),('ryan.simmons@gmail.com','Ryan','Simmons',412036985,'','password','2015-09-04');
/*!40000 ALTER TABLE `user_information` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `viewing_times`
--

DROP TABLE IF EXISTS `viewing_times`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `viewing_times` (
  `tenant_id` int(11) NOT NULL,
  `staff_id` int(11) DEFAULT NULL,
  `house_id` int(11) NOT NULL,
  `time` time(3) DEFAULT NULL,
  `date` date NOT NULL,
  PRIMARY KEY (`tenant_id`,`house_id`,`date`),
  KEY `viewing_tables_staff_id_idx` (`staff_id`),
  KEY `viewing_times_house_id_idx` (`house_id`),
  CONSTRAINT `viewing_times_house_id` FOREIGN KEY (`house_id`) REFERENCES `houses` (`house_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `viewing_times_staff_id` FOREIGN KEY (`staff_id`) REFERENCES `staff_members` (`staff_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `viewing_times_tenant_id` FOREIGN KEY (`tenant_id`) REFERENCES `tenants` (`tenant_id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `viewing_times`
--

LOCK TABLES `viewing_times` WRITE;
/*!40000 ALTER TABLE `viewing_times` DISABLE KEYS */;
INSERT INTO `viewing_times` VALUES (1,1,1,'11:00:00.000','2015-09-20');
/*!40000 ALTER TABLE `viewing_times` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'ifb299'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-10-08 15:07:50
