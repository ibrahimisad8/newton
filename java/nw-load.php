<?php
/**
 * Connection code & file
 * 
 * This file is important to jquery ajax function
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.control-system.ah-engine
 * @link http://www.iblynks.com
 */

/**
 *  Include Config file
 */
include('nw-java-set.inc');
/**
 * Include Javascript class
 */
include(NW_JHTML_CLASS);
/**
 * Check if associative array of variables have been passed to the current script 
 * via the HTTP POST method. Note this can be changed to GET as well but changes
 * need to be made to the jquery ajax function. 
 * <code>
 *   $.ajax({
 *           url  :'ajax.php'
 *           type : 'POST'// Change here   
 *           })
 * </code>
 */

if($_POST)
{ 
    /**
     * General Class
     */
    $system   = new snSystem();
    /**
     * Set array
     */
    $data    = array();
     /**
      * Save all form elements in array
      */
    $process = sn_process_post();
    /**
     * table
     */
    $table   = $process['table'];
    /**
     * table id
     */
    $id      = $process['id'];

    switch($process['key'])
    {
            /*----------------------------------------------------------------------------*/
            /*                               Jquery jason get data                        */
            /*----------------------------------------------------------------------------*/

        case 'jason' : 
            /**
             * query
             */
            $query  = 'select * from '.$table.' where id="'.$id.'"';

            $select = $system->getData('array',$query);

            if(count($select)>0)
            {
                $data['success'] = 1;

                foreach($select as $key=>$value)
                {
                   $data[$key] = $value;
                }

            }
            else{
                   $data['success'] = 0;
                }
                

        break;
        
        /*----------------------------------------------------------------------------*/
        /*                     Jason user ( Job Seeker ) content                      */
        /*----------------------------------------------------------------------------*/
        
        case 'jason-user-cont' : 
            /**
             * query
             */
             $query  = 'select * from nw_users where id="'.$id.'"';

             $select = $system->getData('array',$query);

             if(count($select)>0)
             {   
                 /**
                  * Get users info
                  */
                 $file   = $system->getData('array','select * from nw_files where user="'.$select['security'].'"');
                 $nodata = '<span class="gen-font-one">NO DATA YET</span>';
                 $about  = (empty($select['about']))? $nodata  : $select['about'];
                 $gender = (empty($select['gender']))?$nodata  : $select['gender'];
                 $cv     = cvType($file['format']);
                 $url    = ($cv=='no-file')?'javascript:void(0)':NW_FILE_URL.$file['filename'];
                 /**
                  * Jason data
                  */
                 $data['success'] = 1;

                 $data['header']  = $select['fullname'];

                 $data['content'] = '
                                     <div class="light-box-general-content" >

                                        <div class="light-left-one">
                                            <fieldset class="fieldset-one">
                                                <legend class="legend-one">Details</legend>
                                                <span class="norm-title">&raquo Email </span>
                                                <p>'.$select['email'].'</p>
                                                <span class="norm-title">&raquo Gender</span>
                                                <p>'.$gender.'</p>
                                                <span class="norm-title">&raquo Brief Description</span></p>
                                                <p>'.$about.'</p>
                                            </fieldset>
                                        </div>

                                        <div class="light-right-one">                                        
                                            <fieldset class="fieldset-one">
                                                <legend class="legend-one">CV</legend>
                                                <p>
                                                <a href="'.$url.'" target="_new" class="img-url-one '.$cv.'"/></a>
                                                </p>
                                            </fieldset>
                                        </div>

                                     </div>
                                    ';
             }
             else
             {
                 $data['success'] = 0;
             }
        
            
        break;
        
        /*----------------------------------------------------------------------------*/
        /*                            Jason user(Employer)content                     */
        /*----------------------------------------------------------------------------*/
        
        case 'jason-emp-cont' : 
            /**
             * query
             */
             $query  = 'select * from nw_users where id="'.$id.'"';

             $select = $system->getData('array',$query);

             if(count($select)>0)
             {   
                 /**
                  * Get employers info
                  */
                 $cquery    = 'select * from nw_organization where employer="'.$select['security'].'"';
                 $company   = $system->getData('array',$cquery);
                 $nodata    = '<span class="gen-font-one">NO DATA YET</span>';
                 $about     = (empty($select['about']))? $nodata  : $select['about'];
                 $gender    = (empty($select['gender']))?$nodata  : $select['gender'];
                 $industry  = industry_list('',1);
                 /**
                  * Jason data
                  */
                 $data['success'] = 1;

                 $data['header']  = $select['fullname'];
                 
                 $style = 'style="height:345px;font-size:11px;border-bottom:1px dotted #BBB"';
                 
                 $data['content'] = '
                                     <div class="light-box-general-content" '.$style.'>
                                         
                                            <fieldset class="fieldset-one">
                                                <legend class="legend-one" >Details</legend>
                                                <span class="norm-title">Email </span>
                                                <p>'.$select['email'].'</p>
                                                <span class="norm-title">Gender</span>
                                                <p>'.$gender.'</p>
                                                <span class="norm-title">Brief Description</span></p>
                                                <p>'.$about.'</p>
                                            </fieldset>
                                            
                                            <fieldset class="fieldset-one" style="margin:15px 0px 0px 0px">
                                                <legend class="legend-one">Company details</legend>
                                                <span class="norm-title">Name of company</span>
                                                <p>'.$company['company'].'</p>
                                                <span class="norm-title">Industry</span>
                                                <p>'.$industry[$company['industry']].'</p>
                                                <span class="norm-title">Company Description</span></p>
                                                <p>'.$company['company_desc'].'</p>
                                                <span class="norm-title">Location</span></p>
                                                <p>'.$company['location'].'</p>
                                                <span class="norm-title">Country</span></p>
                                                <p>'.$company['country'].'</p>
                                            </fieldset>
                                            
                                     </div>
                                    ';
             }
             else
             {
                 $data['success'] = 0;
             }
        
            
        break;

        default : $data['success'] = 0;
    }
    
    $ajax = json_encode($data);

    if(!empty($ajax)) 
    { 
        echo $ajax; 
    }
    
}
else
{ 
    die('Access Denied'); 
}

