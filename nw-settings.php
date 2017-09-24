<?php
/**
 * System Settings
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.connection
 * @link http://www.iblynks.com
 */

$system = new config();

/*-------------------------------------------------------------------------*/
/*                               General Define                            */
/*-------------------------------------------------------------------------*/

/**
 * Deafault page url
 */
define('NW_DEFURL',       $system->get_base_url());
/**
 * File Directory
 */
define('NW_DEFDIR',       $system->pagDir());
/**
 * Class Folder
 */
define('NW_CLASS_FLD',    NW_DEFDIR.'class/');
/**
 * Function Folder
 */
define('NW_FUNCTION_FLD', NW_DEFDIR.'function/');
/**
 * Include Folder Name
 */
define('NW_INCLUDE_NAME', 'includes');
/**
 * jQuery java folder Name
 */
define('NW_JAVA', 'java');
/**
 * Iclude Folder
 */
define('NW_INCLUDE_FLD',  NW_DEFDIR.NW_INCLUDE_NAME.'/');
/**
 * Image Folder URL
 */
define('NW_IMAGE_URL',    NW_DEFURL.'images/');
/**
 * Style Folder URL
 */
define('NW_STYLE_URL',    NW_DEFURL.'style/');
/**
 * Style Folder URL
 */
define('NW_SCRIPT_URL',   NW_DEFURL.'script/');
/**
 * Error Folder URL 
 */
define('NW_ERROR_URL',    NW_DEFURL.'error/');
/**
 * File Folder URL 
 */
define('NW_FILE_URL',    NW_DEFURL.'file/');
/**
 * Users home page icons
 */
define('NW_USR_FUNC',    NW_IMAGE_URL.'user-functions/');
/**
 * jQuery Update & Delete
 */
define('NW_JQUPDEL',    NW_DEFURL.NW_JAVA.'/nw-del.php');

/*-------------------------------------------------------------------------*/
/*                               Class Files                               */
/*-------------------------------------------------------------------------*/

/**
 * General Class File
 */
define('NW_GENERAL_CLASS',     NW_CLASS_FLD.'nw-general-class.php');
/**
 * Javascript Html Class
 */
define('NW_JHTML_CLASS',     NW_CLASS_FLD.'nw-javascript-class.php');

/*-------------------------------------------------------------------------*/
/*                               Function Files                            */
/*-------------------------------------------------------------------------*/

/**
 * General Function File
 */
define('NW_GENERAL_FUNCTION',  NW_FUNCTION_FLD.'nw-general-function.php');

/*-------------------------------------------------------------------------*/
/*                                   Cookies                               */
/*-------------------------------------------------------------------------*/

/**
 * Admin Cookie Name
 */
define('NW_ADMIN_COOKIE','newton-admin');
/**
 * User Cookie
 */
define('NW_USER_COOKIE','newton-user');
/**
 * User Cookie
 */
define('NW_EMPLOYEE_COOKIE','newton-employee');