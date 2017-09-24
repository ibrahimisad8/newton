<?php
/**
 * General Function
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.funtion
 * @link http://www.iblynks.com
 */

/**
 * Description :this function sn_date is for setting and date
 * 
 * @param  string         $data
 * @param  string|integer $options
 * @param  string|integer $store
 * @return string date & time
 */
function sn_date($data,$options,$store)
{

    /**
     *  Set Default Time zone 
     */
    date_default_timezone_set('Asia/Kuala_Lumpur');

    switch($data)
    {    
         
        /*----------------------------------------------------------------------------*/
        /*                                Real Time                                   */
        /*----------------------------------------------------------------------------*/
        
         case 'real':

                    switch($options)
                    {

                           case 1: $date =  date("M-D-Y") ;break;

                           case 2: $date =  date("m-d-Y") ;break;

                           case 3: $date =  date("l jS \of F Y h:i:s A");break;

                           case 4: $date = strtotime("now");break;

                     }
         break;
   

         /*----------------------------------------------------------------------------*/
         /*                               Time Change                                  */
         /*----------------------------------------------------------------------------*/
     
         case 'change':

                   /**
                    * Previous Time stored in database normally using strtotime 
                    */
                    switch($options)
                    {

                           case 1: $date =  date("M-D-Y",$store);break;

                           case 2: $date =  date("m-d-Y",$store);break;

                           case 3: $date =  date("l jS \of F Y h:i:s A",$store);break;

                           case 4: $date =  date("H:i A",$store);break;

                           case 5: $date =  date("l jS \of F Y",$store);break;

                           case 6: $date =  date("M-D-Y h:i:s A",$store);break;
                           
                           case 7: $date =  nl2br2(date("<b>d F</b>\nh:i:s a",$store));break;
                           
                           case 8: $date =  date("m/d/Y h:i a",$store);break;

                      }

        break;

        /*----------------------------------------------------------------------------*/
        /*                                 Time Any                                   */
        /*----------------------------------------------------------------------------*/
        
        case 'any' : 

                   /**
                    *  Any time  format 
                    */
                   $date = date($options);
        break;	   


     }

                
    return $date; 
	
}
/** 
 * Description : Handles the dynamic page changing of the web & admin system 
 * 
 * @param string $type         Method post or get
 * @param string $pages_dir    file folder
 * @param string $file_format  file type
 * @param string $def          Default page
 * @param string $opt          Method Options 
 */
function dynamicSys($type,$pages_dir,$file_format,$def,$opt)
{
 
    switch($type)
    {   
        case'GET' : $page  = $_GET[$opt];break;

        case'POST': $page  = $_POST[$opt];break; 

    }   
    /**
     * File format
     */
    define("FILE_FORMAT",$file_format);   
    /**
     * Check method availability
     */
    if($page)
    {
        $pages = scandir($pages_dir, 0);

        unset($pages[0], $pages[1]);

        if (in_array ($page.'.'.FILE_FORMAT, $pages))
        { 
            include ($pages_dir.'/'.$page.'.'.FILE_FORMAT);
        }
        else
        {
           $page = NW_ERROR_URL;

           header('location:'.$page);
        }

    }
    else{

         include($pages_dir.$def.'.'.FILE_FORMAT);

        }

}
/**
 * Description : Fucntion hadles the error messages and success
 * 
 * @param  string $type  The message to display on screen
 * @param  string $data  type of message
 * @param  string $style Extra css style
 * @return string
 */
function system_message ($type,$data,$style)
{	
    if($type=='error')
    {
       $return = "<div class='error $style'> $data </div>"; 
    }
    
    
    if($type=='success')
    {
        $return = "<div class='success $style'> $data </div>";
    }
    
    if($type=='warning')
    {
        $return = "<div class='err-active $style'> $data </div>";
    }
    
    return $return;
}
/** 
 * Description : Handles the postings 
 * @return array returns $_POST global variable 
 */
function sn_process_post()
{   
    $process = array();
    
    foreach ($_POST as $key=>$value)
    {
      $process[$key] = $value ;   
    }
    
    return $process;
}
/** 
 * Description : 
 */
function sn_valid_post($data,$req,$sys)
{   
   $count = 0;
   
   if($sys==1)
   {
        foreach ($data as $key=>$value)
        {
           if(in_array($key,$req)){}
           else
           {
               if(!empty($value))
               {
                  $count +=1; 
               }
               
           }
        }
   }

    
    return $count;
}
/**
 * Description : process file upload
 * 
 * @param  array $file_types file extentions in array
 * @return integer & String
 */
function sn_file_upload($user,$file_types)
{       
    
        // Required data
        $name  = $_FILES['file']['name']; 
        $tmp   = $_FILES['file']['tmp_name']; 
        $error = $_FILES['file']['error'];
        
        // General Class
        $action = new snSystem();
        
        // target folder
        $target = NW_DEFDIR.'file/';
        
        // Intialize update variable
        $update = false;
        
        // Save progress
        $process = array();
        
        // Random variable to replace file name
        $rand  = rand(1234567890,0987654321);

        // Allowed File types
        // $file_types = array('.pdf','.docx');

        //File extention
        $ext = substr($name , strpos($name ,'.'), strlen($name)-1);

        $name = $rand.$ext;
        
        // File upload status
        $process['finish']  = 0;
        
        // File upload messages
        $process['message'] = 'An <b>error</b> occured please try again';
        
        // Check if its the required file  
        if(in_array($ext,$file_types))
        {      
            
                // check if user has uploaded previously
                $check  = $action->getData('all','select * from nw_files where user="'.$_COOKIE[$user].'"');

                if($check['count']>0&&!empty($check['fetch']['filename']))
                {   
                    $remove = unlink($target.$check['fetch']['filename']);

                    if($remove)
                    {
                       $update = true;
                    }
                }
               
               // Check for error
               if($error==0)
               {
                   // If not Error move the file to the target folder
                   if(move_uploaded_file($tmp, $target.$name))
                   {   
                      
                       if($update==1)
                       {
                           $system = $action->ib_update_data('nw_files', array(
                                                                                 'filename' => $name,
                                                                                 'format'   => $ext                                                            
                                                                               ),'where user="'.$_COOKIE[$user].'"');
                           $msg    = 'updated';
                       }
                       else
                       {
                            $system = $action->ib_insert_data('nw_files', array(
                                                                      'id'       => $action->getData('max-col', 'select MAX(id) from nw_files'),
                                                                      'user'     => $_COOKIE[$user],
                                                                      'filename' => $name,
                                                                      'format'   => $ext,
                                                                      'gate'     => 0                                                                 
                                                               ));
                            $msg    = 'uploaded';
                       }
                       
                       // Confirms file has uploaded or update
                       if($system)
                       {
                             $process['finish']  = 1;
                             
                             $process['message'] = 'Your <b>CV</b> has been '.$msg;
                       }

                   }
                   else
                   {
                       $process['message'] = 'The <b>file</b> could not be uploaded ';
                   }

              } 
        }
        else
        {    
            $process['message'] = 'Invalid <b>file</b> format please try again';
        }

        return $process;
        
}
/**
 * Description : Delete file
 * 
 * @param  string  $user get user cookie id or security id
 * @param  integer $act  the type of action
 * @return integer|String
 */
function sn_file_delete($user,$act)
{
    $action = new snSystem();
    // target folder
    $target = NW_DEFDIR.'file/';
    //Action progress
    $process = array();
    // File upload status
    $process['finish']  = 0;    
    // File upload messages
    $process['message'] = 'An <b>error</b> occured please try again';
    // Get active user
    $user   = ($act==1)? $user : $_COOKIE[$user];
    // Check if user exist
    $check  = $action->getData('all','select * from nw_files where user="'.$user.'"');

    if($check['count']>0)
    {
        $remove = unlink($target.$check['fetch']['filename']);
        
        if($remove)
        {
               $delete = $action->getData('query','delete from nw_files where id="'.$check['fetch']['id'].'"');
              
               if($delete)
               {
                   // File upload status
                   $process['finish']  = 1;    
                   // File upload messages
                   $process['message'] = 'Your <b>CV</b> has been <b>deleted</b>';
               }
         }     
        
    }
    
    return $process;
}
/**
 * @param  string  $type first didgit
 * 
 * @return string  $status
 */
function nw_special_check($type)
{   
    
    /**
     * Action Class
     */
    $action   = new snSystem();
    /**
     * Initialize return variable
     */
    $status   = 0;
    /**
     * Check if employer has updated his company profile
     */
    if($type==NW_EMPLOYEE_COOKIE.'_home_warn')
    {   
        /**
         * sql query
         */
        $query = 'select gate from nw_organization where employer="'.$_COOKIE[NW_EMPLOYEE_COOKIE].'"';
        /**
         * Get gate status 1 or 0
         */
        $gate  = $action->getData('single',$query,'gate');
        
        if($gate==0) 
        {   
            $status = system_message('warning','Please <b>update</b> your <b>company profile</b>');
        }
    }
 
    /**
     * Check if user has uploaded his CV
     */
    if($type==NW_USER_COOKIE.'_home_warn')
    {   
        /**
         * sql query
         */
        $query = 'select * from nw_files where user="'.$_COOKIE[NW_USER_COOKIE].'"';
        /**
         * Get gate status 1 or 0
         */
        $count = $action->getData('count',$query,'');
        
        if($count<=0) 
        {   
            $status = system_message('warning','Please <b>upload</b> your <b>curriculum vitae</b> so as to speed up your application process'); 
        }
    }
    
    return $status;
}
/**
 * @param  integer $num first didgit
 * @param  integer $numDigits Digits second digits 
 * @return integer
 */
function leadingZeros($num,$numDigits) 
{
   return sprintf("%0".$numDigits."d",$num);
}
/**
 * List the countries from database
 * 
 * @param  string  $type   type of listing
 * @param  string  $com    data to compare
 * @param  boolean $return want return array or display 
 * @return array
 */
function counties_list($type,$com,$return)
{
    
    if($type=='custom')
    {
        $data  = new snSystem();
        
        $query = $data->getData('query','select * from nw_countries order by name');
        
        $countries = array();
        
        while($fetch = mysql_fetch_assoc($query))
        {
            $countries[$fetch['id']] = $fetch['name'] ;
            
            if($return!==1)
            {
                $selected = '';

                if($com==$fetch['id'])
                {
                    $selected = 'selected="selected"';
                }

                echo '<option value="'.$fetch['id'].'" '.$selected.' >'.ucwords($fetch['name']).'</option>';
            }
        }
    }
    
    if($return==1) 
    {  
       return $countries;
    }

}
/**
 * Description : used in user's home page to display current page
 * 
 * @param  string  $type  Header or Footer
 * @param  string  $title Page Title 
 * @param  boolean $menu  show menu link 
 */
function DynDiv($type,$title,$menu)
{  
    
    if($type=='H'):
        
        ?>
            <div class='main-wrapper'>
                  <div class='page'>
                      <h1>
                          <span>&raquo;</span> 
                          <?php echo $title?> 
                          <?php if($menu==1): ?>                               
                              <span style="float:right">
                                  <a href='<?php echo NW_DEFURL.'?nav=nw-account'?>' title='Menu'>
                                    <img style="border-radius:3px;" src='<?php echo NW_IMAGE_URL.'icons/menu_2.png'?>' />
                                  </a>
                              </span>
                          <?php endif;?>
                          <?php if($menu==2&&(isset($_GET['msc'])||isset($_GET['act']))):?>
                              <?php 
                                 /**
                                  * Go to previous page
                                  */
                                 if(isset($_GET['msc'])) 
                                 {
                                     $url = 'javascript: history.go(-1)';
                                 }
                                 /**
                                  * Go to users function page
                                  */
                                 if(isset($_GET['act']))
                                 {
                                     $url = NW_DEFURL.'?nav='.$_GET['act'];
                                 }
                              ?>
                              <span style="float:right">
                                  <a href='<?php echo $url?>' title='Go Back'>
                                    <img style="border-radius:3px;" src='<?php echo NW_IMAGE_URL.'icons/back-3.png'?>' />
                                  </a>
                              </span>                          
                          <?php endif;?>
                      </h1> 
        <?php
     
    elseif($type=='F') :
        
        ?>
                 </div>
           </div>
        <?php
        
    endif;
    
}
/**
 * @param string $buffer Pass the html text 
 * @return minified html
 */
function compress_page($buffer) 
{
    $search = array(  
                      '!/\*[^*]*\*+([^/][^*]*\*+)*/!'=> '',
                      "/<!--.*?-->/"  => "",                      
                      "/ +/"          => " ",
                      "/\s/"          => " ",
                      "/\s{2,}/"      => " ",                                  
        
                   );
    
     
    $buffer = preg_replace(array_keys($search), array_values($search), $buffer);
    
    return $buffer;

}
/**
 * List the countries from database
 * 
 * @param  string  $type   type of listing
 * @param  string  $com    data to compare
 * @param  boolean $return want return array or display 
 * @return array
 */
function industry_list($com,$return)
{
    
        $data  = new snSystem();
        
        $query = $data->getData('query','select * from nw_industry order by name');
        
        $countries = array();
        
        while($fetch = mysql_fetch_assoc($query))
        {
            $countries[$fetch['id']] = $fetch['name'] ;
            
            if($return!==1)
            {
                $selected = '';

                if($com==$fetch['id'])
                {
                   $selected = 'selected="selected"'; 
                }
                
                echo '<option value="'.$fetch['id'].'" '.$selected.' >'.ucwords($fetch['name']).'</option>';
            }
        }
        
        if($return==1)
        { 
            return $countries;
        }

}
/**
 * Description : users home page link
 */
function home_functions($link,$image,$name,$style)
{
    ?>
     <a href='<?php echo $link?>' class='functions <?php echo $style?>'>
            <i style="background-image:url('<?php echo NW_USR_FUNC.$image?>')" ></i>
            <h3><?php echo $name?></h3>
     </a>
   <?php 
}
/**
 * Description converts <br/> to  " "
 */
function br2nl($string)
{
  return preg_replace('/\<br(\s*)?\/?\>/i', "\n", $string);
}
/**
 * Inserts HTML line breaks before all newlines in a string
 */
function nl2br2($string) 
{ 
    $string = str_replace(array("\r\n", "\r", "\n"), "<br />", $string);
    
    return $string; 
}
/**
 * Shorten text
 */
function ShortenText($text,$chars='190') 
{ 

    $length = strlen($text); 
    $txt1   = $text." "; 
    $txt2   = substr($txt1,0,$chars); 
    $txt3   = substr($txt2,0,strrpos($txt2,' ')); 
    $text   = strip_tags($txt3);  

    if($length > $chars) 
    { 
        $text = $text."..."; 
    } 

    return $text; 

} 
/**
 * Convert text to small lower case then to uppercase first 
 * letter in word(s)
 */
function strtolower_ucfirst($text)
{  
    $data = ucfirst(strtolower($text));
    
    return $data ;
}
/**
 * Shorten text after using strtolower_ucfirst()
 */
function disp_let($text)
{   
    $data = strtolower_ucfirst(ShortenText(br2nl($text)));
    return $data;
}
/**
 * Job invenory & counts
 */
function job_inventory()
{
    $data  = new snSystem();
        
    $count = $data->getData('count', 'select * from nw_jobs');
    
    return strlen($count)+1;
}
/**
 * Description : Job status
 * 
 * @param  int    $fetch type of job status
 * @return string Returns jobs status e.g (Pending , interview, rejected e.t.c)
 */
function job_status($fetch)
{
    switch($fetch)
    {   
          case 1  : $status = 'pending'      ;break;
          case 2  : $status = 'interview'    ;break;
          case 3  : $status = 'rejected'     ;break;
          case 4  : $status = 'employed'     ;break;
          case 5  : $status = 'un subscribed';break;
          default : $status = 'status-error';
    }
    
    return $status;
}
/**
 * Description : Put comapny intial ( NW ) & leading zero to job id
 *  
 * @param  int    $id Job id from database
 * @return string Returns job id with initial & leading zero
 */
function job_id($id)
{
    $newid = 'NW_'.leadingZeros($id,job_inventory());
    
    return $newid;
}
/**
 * Description : Type of file uploaded
 * @param string $fetch file fromat
 */
function cvType($fetch)
{
    switch($fetch)
    {   
        case '.pdf'  : $type = 'pdf';break;
        case '.docx' : $type = 'office';break;
        default      : $type = 'no-file';
    }
    
    return $type;
}
/**
 * Description : Check if data is selected
 * @param string|int $data  variable to verify
 * @param string|int $check variable to check with data
 */
function selected($data,$check)
{
    $selected = ''; 
    
    if($data==$check)
    {
        $selected = "selected='selected'";
    }
    
    return $selected;
}
/**
 * Description : Get user's quick detials
 * 
 * @param  string  $type The type of data to get for the user
 * @param  varchar $user User ID or Security code to get his data
 * @return array   returns the users data in the form of  array
 */
function userDetails($type,$user)
{
    $action  = new snSystem();
    
    $return  = '0';
    
    if($type=='comp-contact')
    {   
        
       $data    = $action->getData('all','select * from nw_organization where employer="'.$user.'"');
       /**
        * Countries list
        */
       $country_list = counties_list('custom','',1);
       
       $return       = $data['fetch']['location'].' '.$data['fetch']['postcode'].'<br>'.
                       $data['fetch']['state'].'<br>'.
                       $country_list[$data['fetch']['country']].'<br>'.
                       $data['fetch']['url'];
    }
    
    return $return;
    
}
/**
 * Encryption using base 64
 * 
 * @param  string  $data   Information or data to encode
 * @return string
 */
function base64url_encode($data) 
{ 

  return rtrim(strtr(base64_encode($data), '+/', '-_'), '='); 

}
/**
 * Dencryption using base 64
 * 
 * @param  string  $data   Information or data to encode
 * @return string
 */
function base64url_decode($data) 
{ 

  return base64_decode(str_pad(strtr($data, '-_', '+/'), strlen($data) % 4, '=', STR_PAD_RIGHT)); 

} 

/*----------------------------------------------------------------------------*/
/*                              Jquery PHP Functions                          */
/*----------------------------------------------------------------------------*/

/**
 * Description : Display html tag for jquery validation
 */
function Jquery_field_msg($name)
{
    $data = '<span class="error-lbox" id="'.$name.'"></span>';
    
    return $data;
    
}

/*----------------------------------------------------------------------------*/
/*                              Security & General Checks                     */
/*----------------------------------------------------------------------------*/

/**
 * Description : Check if user is logged in
 * 
 * @return  varchar Returns users security key
 */
function check_user()
{   
    $user = 'null';
    
    if(isset($_COOKIE[NW_EMPLOYEE_COOKIE]))
    {      
       $user = NW_EMPLOYEE_COOKIE;  
    }
    else if(isset($_COOKIE[NW_USER_COOKIE]))
    {
       $user = NW_USER_COOKIE;
    }
    else
    {
       header('location:'.NW_ERROR_URL.'?action=access-denied');
    }
    
    return $user;
}
/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/


