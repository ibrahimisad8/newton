<?php
/**
 * Admin Index
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.connection
 * @link http://www.iblynks.com
 */

/**
 * Include Configuration file
 */
include('../nw-config.php');
/**
 *  Include General Class
 */
include (NW_GENERAL_CLASS);
/**
 *  Include Function File
 */
include (NW_GENERAL_FUNCTION);


/*-------------------------------------------------------------------------*/
/*                            Admin Define General                         */
/*-------------------------------------------------------------------------*/

/**
 * Define Admin folder 
 */
 define('NW_ADMIN_FLD',    'admin/');
 /**
  * Define Admin Directory
  */
 define('NW_ADMIN_DIR',    NW_DEFDIR . NW_ADMIN_FLD);
 /**
  * Define Admin URL
  */
 define('NW_ADMIN_URL',    NW_DEFURL . NW_ADMIN_FLD);
 /**
  * Define Admin Image Folder
  */
 define('NW_ADMIN_IMG',    NW_ADMIN_URL . 'img/');
 /**
  * Define Admin Syle Folder
  */
 define('NW_ADMIN_STYLE',  NW_ADMIN_URL . 'style/');
 /**
  * Define Admin Function & Class Folder
  */
 define('NW_ADMIN_CODE',   NW_ADMIN_DIR . 'codes/');
 /**
 * Define Admin image function folder
 */
define("NW_ADMIN_FUNIMG",  NW_ADMIN_IMG. 'icon/functions');
 
 
 /*-------------------------------------------------------------------------*/
 /*                       include settings (Dynamic)                        */
 /*-------------------------------------------------------------------------*/
 
 /**
  * Define Admin Include Folder name 
  */
 define('NW_ADMIN_INC',    'inc');
 /**
  * Define Admin Inc Folder path
  */
 define('NW_ADMIN_DYN',     NW_ADMIN_DIR . NW_ADMIN_INC . '/');
 /**
  * Default Dyanamic COntrol Pgae
  */
 define('NW_ADMIN_CONTROL', NW_ADMIN_DYN . 'nw-admin-control.inc');
 /**
  * Define login page
  */
define('NW_ADMIN_LOGIN' ,   NW_ADMIN_DYN . 'nw-admin-login.inc');
?>
