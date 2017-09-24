-- phpMyAdmin SQL Dump
-- version 4.1.12
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Nov 09, 2015 at 09:59 PM
-- Server version: 5.6.16
-- PHP Version: 5.5.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `newton`
--

-- --------------------------------------------------------

--
-- Table structure for table `nw_applicants`
--

CREATE TABLE IF NOT EXISTS `nw_applicants` (
  `id` int(11) NOT NULL,
  `user_id` varchar(51) NOT NULL,
  `employer_id` varchar(101) NOT NULL,
  `job_id` int(11) NOT NULL,
  `status` int(11) NOT NULL COMMENT '(1) Job-pending (2) Interview (3) Rejected (4) Accepted',
  `interview` int(11) NOT NULL,
  `interview_date` varchar(101) NOT NULL,
  `date` varchar(51) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_applicants`
--

INSERT INTO `nw_applicants` (`id`, `user_id`, `employer_id`, `job_id`, `status`, `interview`, `interview_date`, `date`, `gate`) VALUES
(1, '84p9VeSrM7bgi1adl35kZNu2h6jOwqct', '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 1, 1, 0, '', '1422469370', 0),
(2, '84p9VeSrM7bgi1adl35kZNu2h6jOwqct', '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 3, 1, 0, '', '1422469549', 0),
(3, 'r91kcwu3ldf7pqeO2bZ8M6taihjNg54S', 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 8, 1, 0, '', '1446376090', 0),
(4, 'r91kcwu3ldf7pqeO2bZ8M6taihjNg54S', 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 7, 2, 1, '11/02/2015 02:31 pm', '1446376105', 0);

-- --------------------------------------------------------

--
-- Table structure for table `nw_comments`
--

CREATE TABLE IF NOT EXISTS `nw_comments` (
  `id` int(11) NOT NULL,
  `job_id` int(11) NOT NULL,
  `user` int(11) NOT NULL,
  `user_id` varchar(51) NOT NULL,
  `comment` text NOT NULL,
  `date` varchar(51) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_comments`
--

INSERT INTO `nw_comments` (`id`, `job_id`, `user`, `user_id`, `comment`, `date`, `gate`) VALUES
(2, 2, 2, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Wa alaikumusalam how are you\n', '1418029021', 0),
(4, 1, 1, '5tg9cfwMjbhq4S8Ok2Ze6Vurldia3Np1', 'Salaumaliakum How is work hope you are enjoying the website', '1420354715', 0),
(5, 1, 2, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Wa alaikumusalam Yes i am ', '1420354758', 0),
(6, 1, 2, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Please can we add new jobs before the scheduled maintenance ', '1420354800', 0),
(7, 1, 1, '5tg9cfwMjbhq4S8Ok2Ze6Vurldia3Np1', 'Salamualaikum just testing system ', '1422132819', 0);

-- --------------------------------------------------------

--
-- Table structure for table `nw_countries`
--

CREATE TABLE IF NOT EXISTS `nw_countries` (
  `id` int(11) NOT NULL,
  `name` varchar(101) NOT NULL,
  `date` varchar(101) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_countries`
--

INSERT INTO `nw_countries` (`id`, `name`, `date`, `gate`) VALUES
(2, 'Malaysia', '1395139155', 0),
(3, 'Singapore', '1395139169', 0),
(4, 'Indonesia', '1395139178', 0),
(6, 'United States', '1395139208', 0),
(7, 'NIgeria', '1395139294', 0);

-- --------------------------------------------------------

--
-- Table structure for table `nw_feedback`
--

CREATE TABLE IF NOT EXISTS `nw_feedback` (
  `id` int(11) NOT NULL,
  `user` text NOT NULL,
  `email` text NOT NULL,
  `subject` text NOT NULL,
  `message` text NOT NULL,
  `date` varchar(101) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `nw_files`
--

CREATE TABLE IF NOT EXISTS `nw_files` (
  `id` int(11) NOT NULL,
  `user` varchar(51) NOT NULL,
  `filename` varchar(101) NOT NULL,
  `format` varchar(101) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_files`
--

INSERT INTO `nw_files` (`id`, `user`, `filename`, `format`, `gate`) VALUES
(3, '84p9VeSrM7bgi1adl35kZNu2h6jOwqct', '1119882080.pdf', '.pdf', 0),
(4, 'r91kcwu3ldf7pqeO2bZ8M6taihjNg54S', '548412178.pdf', '.pdf', 0);

-- --------------------------------------------------------

--
-- Table structure for table `nw_industry`
--

CREATE TABLE IF NOT EXISTS `nw_industry` (
  `id` int(11) NOT NULL,
  `name` text NOT NULL,
  `date` varchar(101) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_industry`
--

INSERT INTO `nw_industry` (`id`, `name`, `date`, `gate`) VALUES
(1, 'Bussines & Finance', '1395139029', 0),
(2, 'Communication', '1395139029', 0),
(3, 'Computer & IT', '1395139029', 0),
(4, 'Interior design', '1395139029', 0);

-- --------------------------------------------------------

--
-- Table structure for table `nw_jobs`
--

CREATE TABLE IF NOT EXISTS `nw_jobs` (
  `id` int(11) NOT NULL,
  `employer_id` varchar(101) NOT NULL,
  `job_title` text NOT NULL,
  `job_description` text NOT NULL,
  `industry` int(11) NOT NULL,
  `country` int(11) NOT NULL,
  `date` varchar(101) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_jobs`
--

INSERT INTO `nw_jobs` (`id`, `employer_id`, `job_title`, `job_description`, `industry`, `country`, `date`, `gate`) VALUES
(1, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Software Engineer', 'Software engineering is the study and application of engineering to the design, development, and maintenance of software.When the first digital computers appeared in the early 1940s<br /><br /><b>Reqyirements</b><br /><br />(1) Degree in software engineering <br />(2) Likes to work in a group<br />(3) Can solve complex Problems', 3, 7, '1416372460', 0),
(2, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Sales person', 'A sale is the act of selling a product or service in return for money or other compensation.[1] Signalling completion of the prospective stage, it is the beginning of an engagement between customer and vendor or the extension of that engagement.<br /><br /><b>Reqyirements</b><br /><br />(1) Degree in business or public administration<br />(2) Likes to work in a group<br />(3) Can solve complex Problems', 3, 7, '1416378369', 0),
(3, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Database Administartor', 'A database administrator (DBA) is an IT professional responsible for the installation, configuration, upgrading, administration, monitoring, maintenance, and security of databases in an organization.<br /><br /><b>Requirement</b><br /><br />(1) Degree in IT, Networking or any related fields<br />(2) Cisco certifications<br />(3) Good in trouble shooting ', 3, 7, '1416378503', 0),
(4, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Python back-end developer', 'In software engineering, the terms "front end" and "back end" are distinctions which refer to the separation of concerns between a presentation layer and a data access layer respectively.<br /><br />The front end is an interface between the user and the back end. The front and back ends may be distributed amongst one or more systems<br /><br /><b>Reqyirements</b><br /><br />(1) Degree in business or public administration<br />(2) Likes to work in a group<br />(3) Can solve complex Problems<br />', 3, 7, '1419595540', 0),
(5, 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 'Database Administrator', 'A database administrator (DBA) is an IT professional responsible for the installation, configuration, upgrading, administration, monitoring, maintenance, and security of databases in an organization.<br /><br /><b>Requirement</b><br /><br />(1) Degree in IT, Networking or any related fields<br />(2) Cisco certifications<br />(3) Good in trouble shooting ', 1, 3, '1420327559', 0),
(6, 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 'Software Engineer ( Java )', 'Software engineering is the study and application of engineering to the design, development, and maintenance of software.When the first digital computers appeared in the early 1940s<br /><br /><b>Reqyirements</b><br /><br />(1) Degree in software engineering <br />(2) Likes to work in a group<br />(3) Can solve complex Problems', 1, 3, '1420327666', 0),
(7, 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 'Human Resource', 'A sale is the act of selling a product or service in return for money or other compensation.[1] Signalling completion of the prospective stage, it is the beginning of an engagement between customer and vendor or the extension of that engagement.<br /><br /><b>Reqyirements</b><br /><br />(1) Degree in business or public administration<br />(2) Likes to work in a group<br />(3) Can solve complex Problems', 1, 3, '1420327703', 0),
(8, 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 'Accountant', 'A sale is the act of selling a product or service in return for money or other compensation.[1] Signalling completion of the prospective stage, it is the beginning of an engagement between customer and vendor or the extension of that engagement.<br /><br /><b>Reqyirements</b><br /><br />(1) Degree in business or public administration<br />(2) Likes to work in a group<br />(3) Can solve complex Problems', 1, 3, '1420327795', 0);

-- --------------------------------------------------------

--
-- Table structure for table `nw_notice`
--

CREATE TABLE IF NOT EXISTS `nw_notice` (
  `id` int(11) NOT NULL,
  `job_id` int(11) NOT NULL,
  `user_id` varchar(101) NOT NULL,
  `employer_id` varchar(101) NOT NULL,
  `subject` text NOT NULL,
  `message` text NOT NULL,
  `date` varchar(101) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_notice`
--

INSERT INTO `nw_notice` (`id`, `job_id`, `user_id`, `employer_id`, `subject`, `message`, `date`, `gate`) VALUES
(1, 3, '84p9VeSrM7bgi1adl35kZNu2h6jOwqct', '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'NEWTON AGENCY - JOB INTERVIEW', '<p><b>NEWTON MANGEMENT TEAM</b></p><p><b>Dear Ibrahim Isa</b></p><p>You are scheduled to have an interview with an <b>employer</b> as shown below please follow the employers guide or info.</p><br><br><p><b>EMPLOYERS INFORMATION</b></p><p><b>Company</b><br>Iblynks</p><p><b>Industry</b><br>Computer & IT</p><p><b>Job Title</b><br>Database Administartor</p><p><b>Interview date</b><br/>12/21/2014 10:00 am</p><p><b>Meassage</b><br/>Good day Ibrahim Isa</p><p><b>Contact</b><br/>34 Garba Ja Abdul Kadir 430000<br>Niger<br>NIgeria<br>iblynks.com</p>', '1418929592', 0),
(2, 7, 'r91kcwu3ldf7pqeO2bZ8M6taihjNg54S', 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 'NEWTON AGENCY - JOB INTERVIEW', '<p><b>NEWTON MANGEMENT TEAM</b></p><p><b>Dear Amina Isa</b></p><p>You are scheduled to have an interview with an <b>employer</b> as shown below please follow the employers guide or info.</p><br><br><p><b>EMPLOYERS INFORMATION</b></p><p><b>Company</b><br>Iblynks</p><p><b>Industry</b><br>Bussines & Finance</p><p><b>Job Title</b><br>Human Resource</p><p><b>Interview date</b><br/>11/02/2015 02:31 pm</p><p><b>Meassage</b><br/>Good day Amina Isa</p><p><b>Contact</b><br/>34 garba ja abdulkadir road ungwan rimi 430000<br>George town<br>Singapore<br>iblynks.com</p>', '1446483868', 0);

-- --------------------------------------------------------

--
-- Table structure for table `nw_organization`
--

CREATE TABLE IF NOT EXISTS `nw_organization` (
  `id` int(11) NOT NULL,
  `employer` varchar(101) NOT NULL,
  `company` text NOT NULL,
  `url` text NOT NULL,
  `business_no` varchar(101) NOT NULL,
  `telephone` varchar(101) NOT NULL,
  `industry` varchar(101) NOT NULL,
  `company_desc` text NOT NULL,
  `location` text NOT NULL,
  `country` varchar(101) NOT NULL,
  `state` varchar(101) NOT NULL,
  `city` varchar(101) NOT NULL,
  `postcode` varchar(101) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_organization`
--

INSERT INTO `nw_organization` (`id`, `employer`, `company`, `url`, `business_no`, `telephone`, `industry`, `company_desc`, `location`, `country`, `state`, `city`, `postcode`, `gate`) VALUES
(1, '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 'Iblynks', 'iblynks.com', 'NW093838', '0136325767', '3', 'Software engineering', '34 Garba Ja Abdul Kadir', '7', 'Niger', 'Bida', '430000', 1),
(2, 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 'Iblynks', 'iblynks.com', 'NW093839', '0136325767', '1', 'Salam very nice company', '34 garba ja abdulkadir road ungwan rimi', '3', 'George town', 'Bida', '430000', 1);

-- --------------------------------------------------------

--
-- Table structure for table `nw_search_history`
--

CREATE TABLE IF NOT EXISTS `nw_search_history` (
  `id` int(11) NOT NULL,
  `data` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `nw_specialization`
--

CREATE TABLE IF NOT EXISTS `nw_specialization` (
  `id` int(11) NOT NULL,
  `industry_id` int(11) NOT NULL,
  `name` text NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `nw_users`
--

CREATE TABLE IF NOT EXISTS `nw_users` (
  `id` int(11) NOT NULL,
  `fullname` text NOT NULL,
  `email` varchar(55) NOT NULL,
  `gender` varchar(51) NOT NULL,
  `username` varchar(54) NOT NULL,
  `password` varchar(55) NOT NULL,
  `about` text NOT NULL,
  `category` varchar(11) NOT NULL COMMENT '1 - admin,2 - Employee,3 - User',
  `security` varchar(55) NOT NULL,
  `gate` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `nw_users`
--

INSERT INTO `nw_users` (`id`, `fullname`, `email`, `gender`, `username`, `password`, `about`, `category`, `security`, `gate`) VALUES
(1, 'Newton Agency', 'newton@yahoo.com', 'male', 'admin', 'e91e6348157868de9dd8b25c81aebfb9', '', '1', '5tg9cfwMjbhq4S8Ok2Ze6Vurldia3Np1', 0),
(2, 'Ibrahim Isa', 'ibrahimisa.d8@gmail.com', 'male', '', '50b33bc60e3f1a499ee674051251f5dd', 'I am an employer', '2', '3q8Vcpb1M2SZjlhg49kaOudw6t7if5er', 0),
(3, 'Ibrahim Isa', 'ibrahimd8@yahoo.com', '', '', 'bc969d7ff3e2871090418ae7e85b5f9f', 'Salamualaikum', '3', '84p9VeSrM7bgi1adl35kZNu2h6jOwqct', 0),
(4, 'Amina Isa', 'hssd8@yahoo.com', 'female', '', '2480577690609dde67bbe7d0f97b9f4f', 'Salam i am seeking for job', '3', 'r91kcwu3ldf7pqeO2bZ8M6taihjNg54S', 0),
(5, 'Fatima Isa', 'userone@email.com', 'male', '', 'ed2b1f468c5f915f3f1cf75d7068baae', 'Salamualaikum, Just testing', '2', 'qVjhb9p5tSck68eO7gZri1l4d23faNwu', 0);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
