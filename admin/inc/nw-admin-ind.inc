<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
/**
 * Include Javascript class
 */
include(NW_JHTML_CLASS);
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
$data  = $action->getData('all','select * from nw_industry order by id desc','');
?>
<script>
    $(function(){
        /**
         * Loading
         **/
        var mw_admin_red = function(t)
                           {
                             generalLoaDiv(t,'#none','.light-box-form-content');
                           };
        /**
         * Make dix to fixed position
         **/
        make_fix('.link-nav','fix-div-one');
        /**
         * Add new job
         **/ 
        checkAll();
        /**
         * Add Region
         **/        
        $('.add-del-ind').click(function(){
            
            /**
             * Action to add or edit job
             **/
            var action = $(this).attr('act'); 
            /**
             * Default needed variables to make the add & edit job work
             **/
             var need   = {
                             title : 'NEW INDUSTRY',
                             type  : 'new-industry',
                             start : false
                          };
            /**
             * Check if user wants edit job post
             **/       
            if(action=='edit')
            { 
                 need   = {
                             title : 'EDIT INDUSTRY',
                             type  : 'edit-industry',
                             start : true
                           };
            }
            /**
             * Show light box
             **/
            var display = {
                             content : '<?php echo compress_page($jhtml->dContent('industry'))?>',
                             button  : '<?php echo compress_page($jhtml->dButtons())?>'                             
                          };

            iblynks({out :display,width:'639px',height:'425px',type:'header',title:need.title}); 
            /**
             * Light box inputs
             **/
             var hDl  = Array('industry');
            /**
             * Update filed to edit using jason
             **/
             if(need.start==true)
             {   

                 var pid      = $(this).attr('pid');
            
                 var reg_name = $(this).attr('nam'); 
                 
                 $('[name='+hDl[0]+']').val(reg_name);
             }
            /**
             * Process input field
             */
            $('.light-button-type-one').click(function(){
                
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter name of industry';
                 
                 if(process_input(hDl,mSg,'')==false)
                     
                 return false;
                 
                 else
                 { 
                     var info = {
                                    'industry' : $('[name='+hDl[0]+']').val(),
                                    'pid'      : pid,
                                    'type'     : need.type
                                 };
                     /**
                      *Loading
                      */
                     mw_admin_red('show');
                     
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
                                            mw_admin_red('hide'); 
                                            
                                            var e_message = function (m)
                                                          {
                                                              $('.Light-box-msg').fadeIn().html(m).centerIn('.ovl_message');
                                                          };
                                            if(result==1)
                                            
                                              window.location.replace('<?php NW_ADMIN_URL.'?nav=nw-admin-ind'?>');
                                             
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
                              table : 'nw_industry',
                              data  : ids    
                            };

                  $.ajax({

                          url  : '<?php echo NW_DEFURL.NW_JAVA.'/nw-del.php'?>',
                          type : 'POST',
                          data : info,
                          success : function(result){

                                         if(result==1)
                                         {
                                             window.location.replace('<?php NW_ADMIN_URL.'?nav=nw-admin-reg'?>');
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
<div class='system-head'>
    <page><span>&raquo;</span>Industries</page>
</div>

<div class='system-content'> 
    <content>
           <div class='link-nav'>
                <table class='tab-one'>
                     <tr>
                          <td>
                              <a  name='new-job' class='admin-button-one add-del-ind' act='new' >
                                 ADD NEW  
                             </a>
                         </td>
                         <td>
                            <a name='feed-submit' class='admin-button-one general-delete-sys-one' >
                               DELETE 
                            </a>
                         </td>
                         <td style='height:33px'>
                             <div class='process-loading'></div>
                         </td>
                     </tr>
                </table>
          </div>
          <div class='top-content' >
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
                                <input type='checkbox' name='check_all' id='checkbox-1-1' class='admin-checkbox wow'> <label for='checkbox-1-1'></label> 
                             </center>
                            </th>
                           <th>Name</th>
                           <th width='35%'>Date Added</th>
                           <th width='7%'>Action</th>
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
                                              <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='admin-checkbox cl' value='<?php echo $fetch['id']?>'> <label for='checkbox-1-<?php echo $cat;?>'></label> 
                                            </center>
                                        </td>
                                        <td><?php echo ucwords($fetch['name']) ?></td>
                                        <td><?php echo sn_date('change',3,$fetch['date'])?></td>
                                        <td>
                                            <table width='100%' class='table_actions'>
                                               <tr>
                                                   <td class='edit add-del-ind' title='Edit Industry'
                                                        act='edit' 
                                                        pid='<?php echo $fetch['id']?>'
                                                        nam='<?php echo $fetch['name']?>'>
                                                   </td>
                                               </tr>   
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
    </content>
</div>