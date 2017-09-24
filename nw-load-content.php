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
  /**
   * Include Config file
   */
  include ('nw-config.php');
  /**
   *  Include General Class
   */
  include (NW_GENERAL_CLASS);
  /**
   *  Include Function File
   */
  include (NW_GENERAL_FUNCTION);
  /**
   * Define Header file
   */
  define('NW_HOME_HEADER', NW_INCLUDE_FLD.'nw-home-header.inc');
  /**
   * Define Footer file
   */
  define('NW_HOME_FOOTER', NW_INCLUDE_FLD.'nw-home-footer.inc');