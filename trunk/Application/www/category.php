<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'access.inc';
	require_once 'accessdeniedexception.inc';
    require_once 'category.inc';
    require_once 'budget.inc';
    require_once 'factory.inc';
    require_once 'view.inc';
    require_once 'transaction.inc';
    require_once 'activity.inc';   
    require_once 'date.inc';

	try {
	    $fullPage = true;
		$access = new Access();
		$access->authenticate();
		$user = $access->getUser();	
        $smarty = new MySmarty($SMARTY_CONFIG);
		
	    if (!empty($_POST)) {
	       $fullPage = false;
	       $action = htmlentities($_POST['action']);
	       
	       if ($action === "add") {
    	       $categoryName = htmlentities($_POST['categoryName']);
            	    
    	       $transaction = new Transaction(new MySqlDB());
               $transaction->start();
              
    	       $category = Factory::createView(new CategoryKey());
    	       
    	       $category->setUser($user);
    	       $category->setActive(TRUE);
    	       $category->setName($categoryName);

    	       $transaction->commit();
	       } elseif ($action === "remove") {
	           try {
	           $key = htmlentities($_POST['key']);

	           $transaction = new Transaction(new MySqlDB());
               $transaction->start();

	           $categoryItem = Factory::getView(new CategoryKey($key));
	           $categoryItem->setActive(0);

    	       $transaction->commit();
    	       } catch (Exception $e) {
    	           print_r($e);
    	       }
	       }
	          
	    }      		
	    
        $userCategories = Category::getOptions(array("USER_ID" => $user->getId(), "ACTIVE" => 1));
        $allCategories = Category::getOptions(array("ACTIVE" => 1));
        
        $smarty->assign('allCategories', $allCategories);
        $smarty->assign('userCategories', $userCategories);
		
		if ($fullPage) {
    		$smarty->assign('user', $user);
    		$smarty->assign('left_menu', true);
    		$smarty->display('category.tpl');
		} else {
            echo $smarty->fetch('category_list.tpl');
		}
		
	} catch (AccessDeniedException $e) {
		trigger_error('Access Denied');
	} catch (Exception $e) {
		trigger_error('An error has occurred, please try again in a few minutes');
	}
	
?>