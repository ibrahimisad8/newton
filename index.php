<?php
/**
 * Index file
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
$filename = 'nw-load-content.php';
/**
 *  Check if file exist
 */
if (file_exists($filename)) {
    /**
     * Include content file
     */
    include ($filename);
    /**
     * Include Header file
     */
    include NW_HOME_HEADER;
    /**
     * Dynamic Content
     */
    dynamicSys('GET', NW_INCLUDE_FLD, 'inc', 'nw-default', 'nav');
    /**
     * Include Footer
     */
    include NW_HOME_FOOTER;
} else {
    die;
}