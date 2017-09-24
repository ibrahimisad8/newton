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
     
    /*------------------------------------------------------------------------*/
    /*                                 Register                               */
    /*------------------------------------------------------------------------*/
     
    if($process['type']=='register')
    {    
        if($process['full-name']&&$process['email']&&$process['password']&&$process['user'])
        {   
            /**
             *  Check if user exist
             */
            $data  = $action->getData('count','select * from nw_users where email="'.$process['email'].'"');
            
            if($data>0)
            {
                $result = 1;
                
            }else{
                
                $security = $action->randoms();
                
                $insert   = $action->ib_insert_data('nw_users', array(
                                                                      'id'       => $action->getData('max-col', 'select MAX(id) from nw_users'),
                                                                      'fullname' => $process['full-name'],
                                                                      'email'    => $process['email'],
                                                                      'password' => md5($process['password']),
                                                                      'about'    => $process['message'],
                                                                      'category' => $process['user'],
                                                                      'security' => $security 
                                                                    ));
                
                if($insert)
                {   
                    
                    $cookie = 'null';
                    
                    switch($process['user'])
                    {
                        case 3   : $cookie = NW_USER_COOKIE;break;
                            
                        case 2   : 
                                   $insert = $action->ib_insert_data('nw_organization', array(
                                                                      'id'       => $action->getData('max-col', 'select MAX(id) from nw_organization'),
                                                                      'employer' => $security,
                                                                    )); 
                                   if($insert)
                                   {    
                                        $cookie = NW_EMPLOYEE_COOKIE;
                                   }
                        break;
                    }
                    
                    if($cookie!=='null')
                    {
                        $action->set_cook_user($cookie,$security,'null');
                        
                        $result = 2;
                    }
                    
                    
                }
                
            }
        }
         
    }
    
    /*------------------------------------------------------------------------*/
    /*                                   Login                                */
    /*------------------------------------------------------------------------*/  
    
    if($process['type']=='login')
    {
        if($process['username']&&$process['secure'])
        {   
              $data = $action->getData('all','select * from nw_users where email="'.$process['username'].'" and password="'.md5($process['secure']).'"');
    
              if($data['count']>0)
              {   
                  if($data['fetch']['category']=='3'||$data['fetch']['category']=='2')
                  {
                      
                      $cookie = ($process['cat']==$data['fetch']['category'])? $process['cat'] : 0;
                      
                      switch($cookie)
                      {
                        case 3   : $cookie = NW_USER_COOKIE;break;
                            
                        case 2   : $cookie = NW_EMPLOYEE_COOKIE;break;
                            
                        default  : $cookie = 'null';
                      }
                      
                      
                      if($cookie!=='null')
                      {
                            if($action->set_cook_user($cookie,$data['fetch']['security'],'null'))
                            {
                                $result = 1;
                            }
                      }


                 }
             }
            
        }
    }
 
    /*------------------------------------------------------------------------*/
    /*                                Add new job                             */
    /*------------------------------------------------------------------------*/
    
    if($process['type']=='new-job')
    {
        if(sn_valid_post($process,array('type'),1)==3)
        {   
            $data   = $action->getData('all','select * from nw_organization where employer="'.$_COOKIE[NW_EMPLOYEE_COOKIE].'"');
            
            if($data['count']>0)
            {
                $table  = 'nw_jobs';
                $insert = $action->ib_insert_data($table,array(
                                                                     'id'              => $action->getData('max-col', 'select MAX(id) from '.$table),
                                                                     'employer_id'     => $data['fetch']['employer'],
                                                                     'job_title'       => $process['job-title'],
                                                                     'job_description' => nl2br2($process['desc']),
                                                                     'industry'        => $data['fetch']['industry'],
                                                                     'country'         => $data['fetch']['country'],
                                                                     'date'            => sn_date('real',4),
                                                                  ));
                if($insert==1)
                {
                   $result=1;
                } 
            }

        }
    }
    
    
    /*------------------------------------------------------------------------*/
    /*                                 Update job                             */
    /*---------------------------------------------------------------  -------*/
    
    if($process['type']=='edit-job')
    {
        if(sn_valid_post($process,array('type'),1)==3)
        {   
            
            $data   = $action->getData('array','select * from nw_organization where employer="'.$_COOKIE[NW_EMPLOYEE_COOKIE].'"');
            
            $job    = $action->getData('count','select * from nw_jobs where id="'.$process['id'].'"');
            
            if($job>0)
            {
                $table  = 'nw_jobs';
                
                $update = $action->ib_update_data($table,array(
                                                                   'job_title'       => $process['job-title'],
                                                                   'job_description' => nl2br2($process['desc']),
                                                                ), 'where id="'.$process['id'].'"');
                if($update==1) {$result=1;} 
            }

        }
    }
    
    /*------------------------------------------------------------------------*/
    /*                                 Update job                             */
    /*------------------------------------------------------------------------*/
    
    if($process['type']=='interview')
    {
       $application = $action->getData('all','select * from nw_applicants where id="'.$process['app'].'"',''); 
       
       if($application['count']>0)
       {   
           /**
            * Update Applicant
            */
           $update = $action->ib_update_data('nw_applicants',array(
                                                                     'interview'      => 1,
                                                                     'interview_date' => $process['date'],
                                                                     'status'         => 2
                                                                   ),'where id="'.$process['app'].'"');
           /**
            * Message Notice
            */
           $insert = $action->ib_insert_data('nw_notice',array(
                                                                 'id'          => $action->getData('max-col', 'select MAX(id) from nw_notice '),
                                                                 'job_id'      => $application['fetch']['job_id'],
                                                                 'user_id'     => $application['fetch']['user_id'],
                                                                 'employer_id' => $application['fetch']['employer_id'],
                                                                 'subject'     => $process['e_title'],
                                                                 'message'     => $process['send_e'],
                                                                 'date'        => sn_date('real',4),
                                                               ));
           if($update&&$insert)
           {
               $result = 1;
           }
       }
    }
    /*------------------------------------------------------------------------*/
    /*                                Add new region                          */
    /*------------------------------------------------------------------------*/
    if($process['type']=='new-region')
    {
        if($process['region'])
        {   
                $table   = 'nw_countries';
                
                $insert  = $action->ib_insert_data($table,array(
                                                                  'id'   => $action->getData('max-col', 'select MAX(id) from '.$table),
                                                                  'name' => $process['region'],
                                                                  'date' => sn_date('real',4),
                                                              ));
                if($insert==1){$result=1;} 
        }
    }
    
    /*------------------------------------------------------------------------*/
    /*                                Edit region                             */
    /*------------------------------------------------------------------------*/
    
    if($process['type']=='edit-region')
    {
        if($process['region'])
        {   
                $table   = 'nw_countries';
                
                $update  = $action->ib_update_data($table,array( 'name' => $process['region'],
                                                               ),'where id="'.$process['pid'].'"');
                if($update==1){$result=1;} 
        }
    }
    
    /*------------------------------------------------------------------------*/
    /*                                Add Industry                            */
    /*------------------------------------------------------------------------*/
    
    if($process['type']=='new-industry')
    {
        if($process['industry'])
        {   
                $table   = 'nw_industry';
                
                $insert  = $action->ib_insert_data($table,array(
                                                                  'id'   => $action->getData('max-col', 'select MAX(id) from '.$table),
                                                                  'name' => $process['industry'],
                                                                  'date' => sn_date('real',4),
                                                              ));
                if($insert==1) {$result=1;} 
        }
    }
    
    /*------------------------------------------------------------------------*/
    /*                                Edit industry                           */
    /*------------------------------------------------------------------------*/
    
    if($process['type']=='edit-industry')
    {
        if($process['industry'])
        {   
                $table   = 'nw_industry';
                
                $update  = $action->ib_update_data($table,array( 'name' => $process['industry'],
                                                               ),'where id="'.$process['pid'].'"');
                if($update==1) {$result=1;} 
        }
    }
    
    /*------------------------------------------------------------------------*/
    /*                                  New Comment                           */
    /*------------------------------------------------------------------------*/
    
    if($process['type']=='new-comment')
    {
        if($process['comment'])
        {   
                $table   = 'nw_comments';
                
                $insert  = $action->ib_insert_data($table,array(
                                                                  'id'      => $action->getData('max-col', 'select MAX(id) from '.$table),
                                                                  'job_id'  => $process['job_id'],
                                                                  'user'    => $process['user'],
                                                                  'user_id' => $process['user_id'],
                                                                  'comment' => $process['comment'],
                                                                  'date'    => sn_date('real',4),
                                                                  'gate'    => 0
                                                              ));
                if($insert==1) {$result=1;} 
        }
    }
   /**
    * Ajax Result 
    */
    echo($result); 
      
}else{die;}
