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
 * General Class
 */
$action  = new snSystem();
/**
 * Initialize Javascript Class
 */
$jhtml   = new jscript();
/**
 * Comment Class Handler
 */
$comment = new ea_comment();
/**
 * Get Posts
 */
$posts   = sn_process_post();
/**
 * Search data
 */
$jobview = $action->getData('all','select * from nw_jobs where id="'.$_GET['id'].'"');
/***
 * Countries list
 */
$country_list = counties_list('custom','',1);
/**
 * Job application
 */
if(isset($posts['job-id'])&&isset($posts['method']))
{   
    $message = system_message('error','An <b>error</b> occured please try again'); 
    /**
     * SQL apllicants table
     */
    $table   = 'nw_applicants'; 
    /**
     * Apply for job
     */
    if($posts['method']=='2')
    {   
        $query  = 'select * from nw_files where user=';
        $check  = $action->getData('array',$query);
        $action->ib_insert_data($table, array(
                                                  'id'          => $action->getData('max-col', 'select MAX(id) from '.$table),
                                                  'user_id'     => $_COOKIE[NW_USER_COOKIE],
                                                  'job_id'      => $posts['job-id'],
                                                  'employer_id' => $jobview['fetch']['employer_id'],
                                                  'status'      => 1,
                                                  'date'        => sn_date('real',4)    
                                             ));
    }
    /**
     * Unsubscribe 
     */
    if($posts['method']=='1')
    {
        $delete = $action->getData('query','delete from '.$table.' where job_id="'.$posts['job-id'].'" and user_id="'.$_COOKIE[NW_USER_COOKIE].'"');
        
        if($delete)
        {  
           $message = system_message('success','You have <b>unsubscribed</b> successfully');
        }
    }
}
/**
 * Apply for job
 */
$apply   = array();
//url 
$apply['url']    = '?nav=nw-jobseek';
//link name
$apply['name']   = 'LOGIN TO APPLY';
// Action to take
$apply['method'] = 'on';
// Gate
$apply['gate']   = 2;
//Data found
$apply['data']   = 'No data found'; 
/**
 * Check if Job Seeker is logged in
 */
if(isset($_COOKIE[NW_USER_COOKIE]))
{
   $file  = $action->getData('array','select * from nw_files where user="'.$_COOKIE[NW_USER_COOKIE].'"');
    
    $apply['name'] = 'APPLY NOW';
    
    $apply['url']  = 'javascript:void(0)';
    
    if(empty($file['filename']))
    {
         $apply['method'] = 'no-access';
    }
    else
    {   
        $query = 'select * from nw_applicants where user_id="'.$_COOKIE[NW_USER_COOKIE].'" and job_id="'.$_GET['id'].'"';
        
        $check = $action->getData('all',$query);
   
        if($check['count']>0)
        {  
            if($jobview['count']>0)
            {   
                $apply['name']  = 'UN SUBSCRIBE'; 

                $apply['gate']  = 1;

                $message        = system_message('warning','You have <b>applied</b> for this job');
            }
            else
            {
                $apply['data'] ='Sorry the <b>empoyer</b> has deleted this job';
            }
        }
    }
}
/**
 * Check if employer is logged in
 */
if(isset($_COOKIE[NW_EMPLOYEE_COOKIE]))
{
    $apply['url']    = 'javascript:void(0)';
    
    $apply['method'] = 'off';
}
/**
 * Get job ID
 */
$job_id = filter_input(INPUT_GET,'id');
?>

<script> 

    $(function(){
        /**
         * Loading Handler
         **/
        var com_load  = function(t)
                        {
                           generalLoaDiv(t,'#none','.light-box-form-content');
                        };
        /**
         *  Message Handler
         */
        var com_msg = function (m,t)
                      {    
                         var box = $('.Light-box-msg');
                                  
                         if(t=='show')
                         {
                             box.fadeIn().html(m).centerIn('.ovl_message');
                         }
                         else
                         {
                             box.fadeOut();
                         }
                     };
        /**
         * Apply for job
         */
        $('.genp-button').click(function(){
             
           var act = $(this).attr('p');
           
           // User allowed to apply
           if(act=='on')
           {
             generalLoaDiv('show','.generalFadediv','.hold-jquery');
             
             $('.apply-job').submit();
           }
           
           // Not allowed to apply
           if(act=='no-access')
           {
             iblynks({
                      out    : 'Please upload your <b>CV</b> before applying',
                      width  : '368px',
                      height : '196px',
                      type   : 'warning'
                    });
           }
         });
        /**
         * New Comment 
         */
        $('.new-com').click(function(){
            /**
             * Show light box
             */
             var display = {
                              content : '<?php echo compress_page($jhtml->dContent('comment',''))?>',
                              button  : '<?php echo compress_page($jhtml->dButtons())?>'                             
                           };
                           
            iblynks({out :display,width:'515px',height:'359px',type:'header',title:'NEW COMMENT'});
            /**
             * Validate new comment form
             */
            $('.light-button-type-one').click(function(){
                
                // New comment textarea
                var new_comment = $('[name=desc]').val();
                // Validate textarea
                if($.trim(new_comment)=='')
                {
                  com_msg('Please enter comment','show');
                }
                else
                { 
                  com_msg('','hide'); com_load('show');
                  
                  var info = {
                                job_id  : $('[name=job_id]').val(),
                                user_id : $('[name=user_id]').val(),
                                user    : $('[name=user]').val(),
                                comment : new_comment,
                                type    : 'new-comment'
                             };
                  
                  $.ajax({
                           url      : '<?php echo NW_DEFURL.NW_JAVA.'/'?>',
                           type     : 'POST',
                           data     :  info,
                           dataType : 'html',
                           success  : function(result){
                                      /**
                                       * Hide loading
                                       **/
                                       com_load('hide'); 
                                       /**
                                        * Succes Operation
                                        */
                                       if(result==1)
                                       {
                                           window.location.replace('<?php echo  NW_DEFURL.'?nav=nw-viewjob&id='.filter_input(INPUT_GET,'id')?>');
                                       }
                                       else
                                       {    
                                          com_msg('An error occured please try again','show');
                                       }                               
                           }
                  });
                }                
            });
        });
        /**
         * Delete comment 
         */
        $('.del-x').click(function(){
        
            //Light box display & variables
            iblynks({
                        out    : '<?php echo compress_page($jhtml->verifyBut('Are you sure you want to delete the <b>comment</b>'))?>',
                        width  : '395px',
                        height : '215px',
                        type   : 'warning'
                   });  
                   
           var comment_id = $(this).attr('p'); 
           
           var div_id     = $(this).attr('cid'); 
           
            // Yes delete Comment
           $('.yes-button').click(function(){
               
               var info = {table:'nw_comments',type:'delete',data:{id:comment_id}};
                  
               $.ajax({
                        url      : '<?php echo NW_DEFURL.NW_JAVA.'/nw-del.php'?>',
                        type     : 'POST',
                        data     :  info,
                        dataType : 'html',
                        success  : function(result){
                            if(result==1)
                            {
                                $('#'+div_id).fadeOut();iblynks_close();  
                            }
                            else
                            {
                               com_msg('Error please try later','show');
                            }
                        }
               });
     
               
            });
            // No dont delete comment
           $('.no-button').click(function(){iblynks_close();});
        });
    });

</script>

<?php DynDiv('H','View Job',2);?>

      <?php echo $message; ?> 

      <div class='general-content'>
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                <?php 
                   if($jobview['count']>0):   
                  /**
                   * Company details
                   */
                   $company = $action->getData('all','select * from nw_organization where employer="'.$jobview['fetch']['employer_id'].'"'); 
                 ?>   
                      <?php if($company['count']>0):?>
                        <div class='top-content'>
                            <div class='view-search-result'>
                                  <div class='result-hold'>
                                      <div class='job-title-top'>
                                          <p class='p-one'><?php echo $jobview['fetch']['job_title']?></p>
                                          <p class='p-two'><?php echo $company['fetch']['company'].' - '.$company['fetch']['state'].' - '.$country_list[$company['fetch']['country']] ?></p>
                                          <p class='p-three'>Posted on <?php echo sn_date('change',3,$jobview['fetch']['date'])?></p>
                                      </div>
                                  </div>
                                  <div class='result-hold'>
                                      <div class='result-title-block'>Job Description</div>
                                      <div class='result-view'>
                                          <?php echo $jobview['fetch']['job_description']?>
                                      </div>
                                  </div>
                                  <div class='result-hold'>
                                      <div class='result-title-block'>Company details<a name='com'></a></div>
                                      <div class='result-view'>
                                          <p><?php echo $company['fetch']['company_desc']?></p>
                                          <p>
                                              <b>Contact Details</b><br/>
                                              <?php echo $company['fetch']['location'] ?> <?php echo $company['fetch']['postcode'] ?><br/>
                                              <?php echo $company['fetch']['state'] ?><br/>
                                              <?php echo $country_list[$company['fetch']['country']]?><br/>
                                              <?php echo $company['fetch']['url'] ?><br/>
                                          </p>
                                      </div>
                                  </div>
                                 <?php if($comment->logedin_user()>0):?>
                                  <div class='result-hold'>
                                      <div class='result-title-block'>Comments</div>
                                      <div class='result-view'>
                                          <div class='comment'>
                                              <div class='hold-new-comment' style='padding : 9px 0px 7px 0px'>
                                                <a href='javascript:void(0)' class="forum-button new-com">New Comment</a>
                                                <input type='hidden' name='user_id' value='<?php echo $comment->return_user_cookie()?>'/>
                                                <input type='hidden' name='user' value='<?php echo $comment->logedin_user()?>'/>
                                                <input type='hidden' name='job_id' value='<?php echo $job_id ;?>'/>
                                              </div>
                                              <?php if($comment->check_post($job_id)>0):?>
                                                <?php echo $comment->get_comments($job_id)?>
                                              <?php else:?>
                                              <div class='no-comment'>
                                                  <center>
                                                     <p><img src='http://localhost/newton/images/general/data.png' /></p>
                                                     <p>No <b>comment</b> yet</p>
                                                  </center>
                                              </div>
                                              <?php endif;?>
                                          </div>
                                      </div>
                                  </div>
                               <?php endif;?>
                            </div>
                        </div>
                        <div class='bottom-content'>
                            <form method='post' class='apply-job' action='?nav=nw-viewjob&id=<?php echo $_GET['id']?>'>
                                <input type='hidden' name='job-id' value='<?php echo $_GET['id'] ?>' />
                                <input type='hidden' name='method' value='<?php echo $apply['gate']?>' />
                            </form>
                            <a href='<?php echo $apply['url']?>' class='genp-button' p='<?php echo $apply['method']?>'>
                                <?php echo $apply['name']?>
                            </a>
                        </div>
                    <?php else:?>
                      <div class='system-loading-one'>
                           <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                           <p>Sorry this <b>employer</b> no longer exist</p>
                      </div> 
                   <?php endif;?>
                <?php else:?>
                      <div class='system-loading-one'>
                           <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                           <p><?php echo $apply['data']?></p>
                      </div>                  
               <?php endif;?>
               </div>          
      </div>

<?php DynDiv('F','');?>

