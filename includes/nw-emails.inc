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
$user    = check_user();
/**
 * General Class
 */
$action = new snSystem();
/**
 * Initialize Class
 */
$jhtml = new jscript();
/**
 * Data
 */
$data  = $action->getData('all','select * from nw_notice where employer_id="'.$_COOKIE[$user].'" order by id desc','');

?>

<script>

    $(function(){
        
       /**
        * Display message
        */
        var nw_emails_msg  = function(m,e)
                             {
                                iblynks({
                                           out    : m,
                                           width  : '368px',
                                           height : '196px',
                                           type   : 'warning',
                                           title  : 'Error',
                                           error  : e
                                       });
                             }
       /**
        * Make dix to fixed position
        */
        make_fix('.link-nav','fix-div-one');
       /**
        * Add new job
        */ 
        checkAll();       
       /**
        * Delete messages
        */
        $('.del-notice').live('click',function(){
            
                var cbox    = $('.cl:checked');
                /**
                 * Check if at least one job is checked
                 */
                var check   = cbox.length;
            
                if(check>0)
                        {
                        $('.process-loading').show(); 

                        var ids  = mapElem('.cl:checked');

                        var info = {
                                      type  : 'delete',
                                      table : 'nw_notice',
                                      data  : ids    
                                    };

                          $.ajax({

                                  url  : '<?php echo NW_DEFURL.NW_JAVA.'/nw-del.php'?>',
                                  type : 'POST',
                                  data : info,
                                  success : function(result){

                                                 if(result==1)
                                                 {
                                                     window.location.replace('<?php NW_DEFDIR.'?nav=nw-emails'?>');
                                                 }
                                                 else
                                                 { 
                                                     nw_emails_msg('Cannot delete please try agin later',true);

                                                     $('.process-loading').hide(); 
                                                 } 

                                }
                          });
                  }
                  else
                  {
                      nw_emails_msg('Please select at least one notification to <br/><br/><b>delete</b>',false);
                  }
        });
       /**
        * View messages
        */
        $('.view-notice').live('click',function(){ 
           
           /**
            * User sent to
            **/
            var sento   = $(this).attr('set');
            
            var style   = 'style="height:345px;font-size:11px;border-bottom:1px dotted #BBB"';
            
            var message = '<div class="light-box-general-content" '+style+'>'+
                             '<div class="norm-title-email">Subject</div>'+
                             '<div class="norm-msg">'+
                                $(this).attr('sub')+
                             '</div>'+
                             '<div class="norm-title-email">Message</div>'+
                             '<div class="norm-msg">'+
                                $(this).attr('msg')+
                             '</div>'+
                          '</div>';
           /**
            * Show light box
            **/
            iblynks({
                       out    : {content : message},
                       width  : '685px',
                       height : '485px',
                       type   : 'header',
                       title  : 'to : '+sento
                   });
        });         
          
    });

</script>

<?php DynDiv('H','Notifications',true);?>

      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <form action='#' method='post'>
                       <?php if($data['count']>0):?>
                          <div class='link-nav'>
                             <table class='tab-one'>
                                 <tr>
                                     <td>
                                       <a  name='new-job' class='general-but-one del-notice'>
                                          DELETE  
                                       </a>
                                       </td>
                                       <td style='height:33px'>
                                           <div class='process-loading'></div>
                                       </td>
                                  </tr>
                             </table>
                          </div>                       
                          <div class='top-content'>
                           <div class='table-min-height'>
                                <table class='tab_admin'>
                                    <tr>
                                        <th width='3%'>
                                            <center> 
                                                <input type='checkbox' name='check_all' id='checkbox-1-1' class='regular-checkbox wow'> <label for='checkbox-1-1'></label> 
                                            </center>
                                        </th>
                                        <th width='11%'>Job Id</th>
                                        <th>Sent to</th>
                                        <th width='33%'>Date sent</th>
                                        <th width='9%'>Action</th>
                                    </tr>
                                    <?php 
                                      /**
                                       * Check box increment
                                       */
                                      $cat = 2;
                                      /**
                                       * Display the data
                                       */
                                      while($fetch = mysql_fetch_assoc($data['query']))
                                      {    
                                          
                                          $user = $action->getData('array','select * from nw_users where security="'.$fetch['user_id'].'"');
                                          
                                          if(count($user)>0)
                                          {
                                               ?> 
                                                <tr>
                                                    <td>
                                                        <center> 
                                                            <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='regular-checkbox cl' value='<?php echo $fetch['id']?>'> <label for='checkbox-1-<?php echo $cat;?>'></label> 
                                                        </center>
                                                    </td>
                                                    <td><?php echo job_id($fetch['job_id'])?></td>
                                                    <td><?php echo ucwords($user['fullname'])?></td>
                                                    <td><?php echo sn_date('change',3,$fetch['date'])?></td>
                                                    <td>
                                                        <table width='100%' class='table_actions'>
                                                         <tr>
                                                             <td class='view view-notice' title='View Message'
                                                                 set="<?php echo $user['fullname']?>"
                                                                 sub="<?php echo $fetch['subject']?>" 
                                                                 msg="<?php echo $fetch['message']?>">
                                                             </td>
                                                         </tr>   
                                                        </table>
                                                    </td>
                                                </tr>
                                              <?php
                                          
                                              $cat +=1;
                                          }
                                          
                                      }
                                    ?>                              
                                </table>
                           </div>
                          </div>
                       <?php else:?>
                           <div class='top-content'>
                              <div class='system-loading-one'>
                                   <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                                   <p>No data yet</p>
                              </div>
                           </div>
                       <?php endif;?> 
                   </form>
               </div>
                   
      </div>

<?php DynDiv('F','');?>

