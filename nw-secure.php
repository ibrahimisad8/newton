<?php
/**
 * Secure login for admin 
 * 
 * This file is important to for secure login by admin
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
$filename = 'nw-load-content.php';

if(file_exists($filename))
{   
    /**
     * Include filename
     */
    include($filename);
    /**
     * Check if user  Id & category is set
     */
    $security = filter_input(INPUT_GET,'userid');
    
    $category = filter_input(INPUT_GET,'category');

    if(isset($security)&&isset($category))
    {  
       /**
        * Intialize Class snSystem 
        */
       $action = new snSystem();
       /**
        * Get employer or jobseeker cookie name
        */
       $cookie_name = ($category==2) ? NW_EMPLOYEE_COOKIE : NW_USER_COOKIE;
       /**
        * Set cookie data
        */
       $cookie_data = $security;
       /**
        * Set cookie
        */
       $action->set_cook_user($cookie_name,$cookie_data,'/?nav=nw-account');
    }
    
}else{die ;}