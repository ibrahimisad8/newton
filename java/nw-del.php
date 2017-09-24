<?php
/**
 * Java script ajax jquery
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package Template
 * @link http://www.iblynks.com
 */
/**
 *  Include Config file
 */
include('nw-java-set.inc');
/**
 * Check if post is used
 */
if($_POST)
{  
    /**
     * Save all form elements in array
     */
    $process = sn_process_post();
    /**
     * Action Class
     */
    $action   = new snSystem();
    /**
     * Ajax result output intialization
     */
    $result  = 0;    
    
    /*----------------------------------------------------------------------------*/
    /*                               General Delete                               */
    /*----------------------------------------------------------------------------*/
    
    if($process['type']=='delete')
    {
        /**
         * Get table
         */
         $table = $process['table'];
         /**
          * Error message 
          */
         $error = 0;
         /**
          * Condition
          */
         foreach($_POST['data'] as $data)
         {  
            $delete = $action->getData('query','delete from '.$table.' where id="'.$data['id'].'"');
            
	    if(!($delete))
            {
                $error +=1;
            }
	
         }
         
         if($error==0){ $result = 1;}
    }
    
    /*----------------------------------------------------------------------------*/
    /*                               Delete Users                                 */
    /*----------------------------------------------------------------------------*/
    if($process['type']=='delete_users')
    {
        /**
         * Get table
         */        
        $table = 'nw_users';
        /**
         * Error Message
         */
        $del_jobseeker = $del_employer = $error = 0;
        
        foreach ($_POST['data'] as $data)
        {   
            // Get users data
            $get_sec   = $action->getData('array','select * from nw_users where id="'.$data['id'].'"','');
            // Employer
            if($get_sec['category']==2)
            {   
                $delete_orgnization = $action->getData('query','delete from nw_organization where employer="'.$get_sec['security'].'"','');
                $delete_jobs        = $action->getData('query','delete from nw_jobs where employer_id="'.$get_sec['security'].'"','');
                $delete_applicants  = $action->getData('query','delete from nw_applicants where employer_id="'.$get_sec['security'].'"','');
                $delete_notice      = $action->getData('query','delete from nw_notice where employer_id="'.$get_sec['security'].'"','');
                $del_employer       = 1;
            }
            // Job Seeker
            if($get_sec['category']==3)
            {   
                // Delete file from folder
                $delete_file   = sn_file_delete($get_sec['security'],1); 
                $delete_fileDB = $action->getData('query','delete from nw_files where user="'.$get_sec['security'].'"','');
                $del_jobseeker = 1;
            }
            // Delete user from DB
            if($del_employer==1||$del_jobseeker==1)
            {
                $delete = $action->getData('query','delete from '.$table.' where security="'.$get_sec['security'].'"');
                
	        if(!($delete))
                {
                  $error += 1;
                }  
            }
        
            
        }
        
        if($error==0){$result = 1;}
    }
    
    /*----------------------------------------------------------------------------*/
    /*                                  Update                                    */
    /*----------------------------------------------------------------------------*/    
    if($process['type']=='update')
    {
         /**
          * Error message 
          */
         $error = 0;
         /**
          * Condition
          */
        foreach($process['data'] as $data)
        {  
            $update = $action->ib_update_data($process['table'],array(
                                                                        $process['col'] => $process['action']
                                                                      ),'where id="'.$data['id'].'"');
            
	    if(!($update))
            {
                $error +=1;
            }
	
       }
       
       if($error==0) {$result = 1;}
    }
    
   /**
    * Ajax Result 
    */
    echo($result); 
      
}else{die;}

