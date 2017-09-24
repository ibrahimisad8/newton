<?php
/**
 * General Class
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.connection
 * @link http://www.iblynks.com
 */

class jscript 
{
    public $disp;
   /**
    * Description : Get form content for light box
    * 
    * @param  string $type Pass the html text 
    * @return string
    */
    public function dContent($type,$user)
    {   
        /**
         * Action class
         */
        $action = new snSystem();
        /**
         * Start form content
         */
        $this->disp = '
                          <div class="generalFadediv" id="none"></div>
                          <div class="light-box-form-content">
                      ';   
        
        /*-----------------------------------------------------------------------------------*/
        /*                                      Register                                     */
        /*-----------------------------------------------------------------------------------*/
        
        if($type=='register')
        {
            $this->disp  .= '  
                               <p>
                                   <label >Full name</label>
                                   <input type="text" class="text-input" name="full-name" >
                                   '.Jquery_field_msg('full-name').'
                                </p>                              
                                <p>
                                   <label>Email</label>
                                   <input type="email" class="text-input" name="email" >
                                   '.Jquery_field_msg('email').'
                                </p>                              
                                <p>
                                   <label>Password</label>
                                   <input type="password" class="text-input" name="password" >
                                   '.Jquery_field_msg('password').'
                                </p>                              
                                <p>
                                   <label>About me</label>
                                   <textarea  name="aboutme" class="text-input" ></textarea>
                                </p>
                            ';
        }
        
        /*-----------------------------------------------------------------------------------*/
        /*                                      Add jobs                                     */
        /*-----------------------------------------------------------------------------------*/  
        
        if($type=='add-job')
        {
            
            $data         = $action->getData('single','select * from nw_organization where employer="'.$_COOKIE[$user].'"','industry');
               
            $industry     = industry_list('',1);
            
            $this->disp  .= '  
                            <table class="table-light-one">
                                <tr>
                                    <td><label class="label-input" >Job title</label></td>
                                    <td><input type="text" name="job-title"  class="text-input s-jinput" /></td>
                                    <td> '.Jquery_field_msg("job-title").'</td>
                                </tr>
                                 <tr>
                                    <td><label class="label-input" >Industry</label></td>
                                    <td>
                                        <input type="text" class="text-input text-disabled s-jinput"  disabled="disabled" value="'.$industry[$data].'"/>
                                        <input type="hidden" name="id" value="null" />
                                    </td>
                                    <td> '.Jquery_field_msg("industry").'</td>
                                </tr>
                                <tr>
                                    <td><label class="label-input" >Job Description</label></td>
                                    <td><textarea name="desc" class="text-input s-jinput s-jtarea"></textarea></td>
                                    <td> '.Jquery_field_msg("desc").'</td>
                                </tr>
                            </table>
                            ';
        }
        /*-----------------------------------------------------------------------------------*/
        /*                                     Applicant Data                                */
        /*-----------------------------------------------------------------------------------*/
        if($type=='get-app')
        {
              $data  = $action->getData('array','select * from nw_users where id="'.$user.'"');
              
              $this->disp .= ''; 
        }
        
        /*-----------------------------------------------------------------------------------*/
        /*                                     notiFication                                  */
        /*-----------------------------------------------------------------------------------*/
        if($type=='interview')
        {
            $data         = $action->getData('single','select * from nw_users where id="'.$_COOKIE[$user].'"','industry');
               
            $industry     = industry_list('',1);
            
            $this->disp  .= '  
                            <table class="table-light-one">
                                <tr>
                                    <td><label class="label-input" >Applicant</label></td>
                                    <td>
                                        <input type="text" class="text-input s-jinput" name="app-data" disabled="disabled"/>
                                    </td>
                                    <td> '.Jquery_field_msg("app-data").'</td>
                                </tr>
                                 <tr>
                                    <td><label class="label-input" >Job Title</label></td>
                                    <td>
                                        <input type="text" class="text-input s-jinput"  name="job-title"/>
                                    </td>
                                    <td> '.Jquery_field_msg("job-title").'</td>
                                </tr>
                                <tr>
                                    <td><label class="label-input" >Date & Time</label></td>
                                    <td>
                                        <input type="text" class="text-input s-jinput" name="interview-date"  />
                                    </td>
                                    <td> '.Jquery_field_msg("interview-date").'</td>
                                </tr>
                                <tr>
                                    <td><label class="label-input" >Message</label></td>
                                    <td>
                                        <textarea name="interview-msg" class="text-input s-jinput s-jtarea-two"></textarea>
                                    </td>
                                    <td> '.Jquery_field_msg("interview-msg").'</td>
                                </tr>
                            </table>
                            ';
        }

        /*-----------------------------------------------------------------------------------*/
        /*                                   Admin add region                                */
        /*-----------------------------------------------------------------------------------*/
        
        if($type=='region')
        {
            $this->disp.='
                          <div >
                                <table class="table-light-one">
                                    <tr>
                                        <td><label class="label-input" >Name</label></td>
                                        <td>
                                             <input type="text" class="text-input" name="region" />
                                        </td>
                                        <td> '.Jquery_field_msg("region").'</td>
                                    </tr>
                                 </table>
                                 <div class="norm-title">
                                     MAP
                                 </div>
                                 <div style="padding-top:13px">
                                    <center>
                                       <a href="'.NW_ADMIN_IMG.'general/map.png" target="_blank">
                                          <img src="'.NW_ADMIN_IMG.'general/map.png" class="img-map" />
                                       </a>
                                     </center>
                                 </div>
                            </div>
                         ';
        }
        /*-----------------------------------------------------------------------------------*/
        /*                                   Admin add industry                               */
        /*-----------------------------------------------------------------------------------*/
        
        if($type=='industry')
        {
            $this->disp.='
                          <div >
                                <table class="table-light-one">
                                    <tr>
                                        <td><label class="label-input" >Name</label></td>
                                        <td>
                                             <input type="text" class="text-input" name="industry" />
                                        </td>
                                        <td> '.Jquery_field_msg("industry").'</td>
                                    </tr>
                                 </table>
                                 <div class="norm-title">
                                     Global Industry performance  
                                 </div>
                                 <div style="padding-top:13px">
                                    <center>
                                       <a href="'.NW_ADMIN_IMG.'general/eng.gif" target="_blank">
                                          <img src="'.NW_ADMIN_IMG.'general/eng.gif" class="img-map" />
                                       </a>
                                     </center>
                                 </div>
                            </div>
                         ';
        }
        /*-----------------------------------------------------------------------------------*/
        /*                                    Add New Comment                                */
        /*-----------------------------------------------------------------------------------*/
        if($type=='comment')
        {
            $this->disp.='
                          <div style="padding-top:7px">
                            <center>
                             <textarea name="desc" class="text-input s-jinput s-jtarea" style="width:465px"></textarea>
                            </center>
                          </div>
                         ';
        }        
        /**
         * End form content
         */
        $this->disp .='</div>';
        /**
         * Check if type is active
         */
        if(!empty($type)) 
        {
            return $this->disp;
        }
        
    }
   /**
    * Description : Get form buttons
    * 
    * @return string
    */    
    public function dButtons()
    {
        $this->disp = '<button class="light-button-type-one">SUBMIT</button>'; 
        
        return $this->disp;
    }
    /**
    * Description : Get verification yes & no buttons
    * 
    * @param  string $data Pass the message 
    * @return string
    */   
    public function verifyBut($data)
    {
        $this->disp = '
                        <p>'.$data.'</p>
                           <p>
                               <button class="light-button-type-two yes-button">YES</button>
                               <button class="light-button-type-two no-button">NO</button>
                           </p>
                      ';
        
        return $this->disp;
    }
}

