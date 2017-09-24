<?php
/**
 * Sn-user-login
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package Template
 * @link http://www.iblynks.com
 */
/**
 * Include Javascript class
 */
include(NW_JHTML_CLASS);
/**
 * Check if user is logged in
 */
$user     = check_user();
/**
 * General Class
 */
$action   = new snSystem();
/**
 * Initialize Class
 */
$jhtml    = new jscript();
/**
 * Get Posts
 */
$posts    = sn_process_post();
/**
 * Off display message
 */
$onmsg    = false;
/**
 * Validate Upload form
 */
if(isset($posts['upload']))
{   
   $process = sn_file_upload($user,array('.pdf','.docx'));$onmsg = true;
}
/**
 * Validate delete form
 */
if(isset($posts['delete-cv']))
{  
   $process =  sn_file_delete($user,0);$onmsg = true;
}
/**
 * Display message
 */
if($onmsg==true)
{
    /**
     * File upload error message
     */ 
    $message = system_message('error',$process['message']); 
    /**
     * File upload success message
     */
    if($process['finish']=='1')
    {    
        $message = system_message('success',$process['message']); 
    }
}
/**
 * Get users file
 */
$data = $action->getData('all','select * from nw_files where user="'.$_COOKIE[$user].'"');
/**
 * Display icon intialization
 */
$display      = array();
$display[1]   = '';        // Detele (x) icons
$display[2]   = '#';       // File Name (xxx.pdf,xxx.docx)
$display[3]   = 'no-file'; // File Type, default no type
$display[4]   = '';        // Target open in new tab of null

if($data['count']>0&&!empty($data['fetch']['filename']))
{   
    /**
     * Set new
     */
    $display[1]   = "<span class='del-cv' title='Delete file'></span>";
    $display[2]   = NW_FILE_URL.$data['fetch']['filename'];
    $display[3]   = 'office';// Word document
    $display[4]   = 'target="_new"';
    /**
     * Cehck if the file is pdf
     */
    if($data['fetch']['format']=='.pdf')
    {   
      $display['3'] = 'pdf';
    }
}
?>
<script>
    $(function(){
        /**
         * Upload or edit cv
         **/
        $('[name="file"]').change(function(){

            generalLoaDiv('show','.generalFadediv','.hold-jquery');

            $('.upload-form').submit();
        });
        /**
         * Delete CV
         */
        $('.del-cv').click(function(){
            
           iblynks({
                      out    : '<?php echo compress_page($jhtml->verifyBut('Are you sure you want to delete'))?>',
                      width  : '395px',
                      height : '225px',
                      type   : 'warning'
                  });    
                  
           /**
            * Yes Delete
            */
           $('.yes-button').click(function(){
              
              generalLoaDiv('show','.generalFadediv','.hold-jquery');
              
              $('.delete-form').submit();iblynks_close();
           });
           /**
            * No dont delete
            */
           $('.no-button').click(function(){
               
               iblynks_close();
               
           });
           
        });
        
        
    });
</script>

<?php DynDiv('H','Curriculum vitae',true);?>

    <?php echo $message; ?> 

    <div class='general-content'>
        
        <div class='generalFadediv genFadediv-border-radius'></div>   
        
        <div class='hold-jquery'>
                <div class='top-content'>

                    <div class='instruction-cv'>
                        <p><b>INSTRUCTION</b></p>
                        <p></p>
                        <p>You can upload your <b>curriculum vitae</b> here the file format allowed are <b>pdf</b> & <b>word document</b> click on the file icon to</p>
                        <p>view. When you want to update the file just upload a new one.</p>
                    </div>

                    <div class='upload-cv'>
                        <div class='center-middle'>
                            <div class='info-top'>
                                <?php echo $display[1];?>
                                <form action='#' method='post' class='delete-form'>
                                    <input type='hidden' name='delete-cv' /> 
                                </form>
                            </div>
                            <a href='<?php echo $display[2];?>' class='d-img <?php echo $display[3];?>' <?php echo $display[4];?> title='View file'></a>
                        </div>
                        <div class='right-file'>
                            <form action='#' method='post' class='upload-form'  enctype='multipart/form-data' >
                                <input type='file'  name='file'/>
                                <input type='hidden' name='upload'  />
                            </form>
                        </div>
                    </div>
                </div>
        </div>       
    </div>

<?php DynDiv('F','');?>

