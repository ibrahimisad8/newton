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
$data  = $action->getData('all','select * from nw_jobs where employer_id="'.$_COOKIE[$user].'" order by id asc','');
?>

<script>

    $(function(){
        
        /**
         * Loading
         **/
        var myLoad  = function(t)
                      {
                         generalLoaDiv(t,'#none','.light-box-form-content');
                       }
        /**
         * Make dix to fixed position
         **/
        make_fix('.link-nav','fix-div-one');
        /**
         * Add new job
         **/ 
        checkAll();
        /**
         * Add or delete job ads
         **/
       $('.add-del-job').click(function(){ 
            /**
             * Action to add or edit job
             **/
            var action = $(this).attr('act');
            /**
             * Default needed variables to make the add & edit job work
             **/
             var need   = {
                             title : 'NEW JOB',
                             type  : 'new-job',
                             start : false
                          };
            /**
             * Check if user wants edit job post
             **/       
            if(action=='edit')
            {   
                
                var need   = {
                                title : 'EDIT JOB',
                                type  : 'edit-job',
                                start : true,
                                ids   : $(this).attr('p')
                              };
                  
            }
            /**
             * Show light box
             **/
             var display = {
                              content : '<?php echo compress_page($jhtml->dContent('add-job',$user))?>',
                              button  : '<?php echo compress_page($jhtml->dButtons())?>'                             
                           }

            iblynks({out :display,width:'819px',height:'495px',type:'header',title: need.title});
            /**
             * Light box inputs
             **/
             var hDl  = Array('job-title','desc','id');
            /**
             * Update filed to edit using jason
             **/
             if(need.start==true)
             {
                var  info = {
                                key   : 'jason',
                                table : 'nw_jobs',
                                id    : need.ids
                            };
                            
                /**
                 * Display loading
                 **/
                 myLoad('show');
                 
                 $.ajax({
                          url      : '<?php echo NW_DEFURL.NW_JAVA.'/nw-load.php'?>',
                          type     : 'POST',
                          data     :  info,
                          dataType : 'json',             
                          success  : function(result){
                                    
                                    // Job tilte
                                    $('[name='+hDl[0]+']').val(result.job_title);
                                    // Job description
                                    $('[name='+hDl[1]+']').val(br2nl(result.job_description));
                                    // required id
                                    $('[name='+hDl[2]+']').val(result.id);
                               
                         }
                 });  

                 /**
                  * Display loading
                  **/
                  myLoad('hide');
         
             }
            /**
             * Process input field
             */
            $('.light-button-type-one').click(function(){
                
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter job title';
                 mSg[hDl[1]] = 'Please enter job description';
                 
                 if(process_input(hDl,mSg,'')==false)
                     
                 return false
                 
                 else
                 { 
                     var info = {
                                    'job-title' : $('[name='+hDl[0]+']').val(),
                                    'desc'      : $('[name='+hDl[1]+']').val(),
                                    'id'        : $('[name='+hDl[2]+']').val(),
                                    'type'      : need.type
                                 };
                     /**
                      *Loading
                      */
                     myLoad('show');
                     
                     $('.Light-box-msg').fadeOut();
                     
                     $.ajax({
                                 url      : '<?php echo NW_DEFURL.NW_JAVA.'/'?>',
                                 type     : 'POST',
                                 data     : info,
                                 dataType : 'html',
                                 success  : function(result){                                              
                                           /**
                                            * Hide loading
                                            **/
                                            myLoad('hide'); 
                                            
                                            var e_message = function (m)
                                                          {
                                                              $('.Light-box-msg').fadeIn().html(m).centerIn('.ovl_message');
                                                          }
                                            if(result==1)
                                            
                                              window.location.replace('<?php NW_DEFDIR.'?nav=nw-jobads'?>');
                                             
                                            else
                                                
                                              e_message('An error occured');
                                 }
                                 
                       });

                 }
                
            });

       });
       
       /**
        * Delete Job Adds
        **/
        $('.general-delete-sys-one').live('click',function(){

                $('.process-loading').show(); 

                 var ids  = mapElem('.cl:checked');

                 var info = {
                              type  : 'delete',
                              table : 'nw_jobs',
                              data  : ids    
                            };

                  $.ajax({

                          url  : '<?php echo NW_DEFURL.NW_JAVA.'/nw-del.php'?>',
                          type : 'POST',
                          data : info,
                          success : function(result){

                                         if(result==1)
                                         {
                                             window.location.replace('<?php NW_DEFDIR.'?nav=nw-jobads'?>');
                                         }
                                         else
                                         { 
                                             iblynks({out :'Cannot delete please try agin later',width:'368px',height:'196px',type:'warning',title:'Error',error:true});

                                             $('.process-loading').hide(); 
                                         } 

                        }
                  });

          });
    });

</script>

<?php DynDiv('H','Job Advertisement',true);?>

    <?php //echo $message; ?> 

      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <form action='#' method='post'>
                       <div class='link-nav'>
                         <table class='tab-one'>
                          <tr>
                            <td>
                            <a  name='new-job' class='general-but-one add-del-job' act='add' >
                              ADD NEW  
                            </a>
                           </td>
                           <td>
                            <a name='feed-submit' class='general-but-one general-delete-sys-one' >
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
                           <?php if($data['count']==0):?>
                                <div class='system-loading-one'>
                                     <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                                     <p>No data yet</p>
                                </div>
                           <?php else:?>
                           <div class='table-min-height'>
                                <table class='tab_admin'>
                                    <tr>
                                        <th width='3%'>
                                            <center> 
                                                <input type='checkbox' name='check_all' id='checkbox-1-1' class='regular-checkbox wow'> <label for='checkbox-1-1'></label> 
                                            </center>
                                        </th>
                                        <th>Job title</th>
                                        <th width='35%'>Date Added</th>
                                        <th width='15%'>Action</th>
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
                                          ?> 
                                                <tr>
                                                    <td>
                                                        <center> 
                                                            <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='regular-checkbox cl' value='<?php echo $fetch['id']?>'> <label for='checkbox-1-<?php echo $cat;?>'></label> 
                                                        </center>
                                                    </td>
                                                    <td><?php echo ucwords($fetch['job_title'])?></td>
                                                    <td><?php echo sn_date('change',3,$fetch['date'])?></td>
                                                    <td>
                                                        <table width='100%' class='table_actions'>
                                                         <tr><td class='edit add-del-job' act='edit' p='<?php echo $fetch['id']?>'></td><td class='view'></td></tr>   
                                                        </table>
                                                    </td>
                                                </tr>
                                             
                                          <?php
                                          
                                          $cat +=1;
                                      }
                                    ?>                              
                                </table>
                           </div>
                         <?php endif;?>
                       </div>
                   </form>
               </div>     
      </div>

<?php DynDiv('F','');?>

