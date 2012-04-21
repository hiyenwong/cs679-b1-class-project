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
    	       $categoryId = htmlentities($_POST['categoryId']);
    	       //TODO: check amount is valid
    	       $budgetedAmount = htmlentities($_POST['budgetedAmount']);
            	    
            	    
    	       $transaction = new Transaction(new MySqlDB());
               $transaction->start();
                    
    	       $budget = Factory::createView(new BudgetKey());
    	       $category = Factory::getView(new CategoryKey($categoryId));
    	       
    	       $budget->setUser($user);
    	       $budget->setActive(TRUE);
    	       $budget->setAmount($budgetedAmount);
    	       $budget->setCategory($category);
    	       
    	       $transaction->commit();
	       } elseif ($action === "remove") {
	           $key = htmlentities($_POST['key']);
	           
	           $transaction = new Transaction(new MySqlDB());
               $transaction->start();
               
	           $budgetItem = Factory::getView(new BudgetKey($key));
	           $budgetItem->setActive(0);
	           
    	       $transaction->commit();
	       }
	          
	    }      		
		
		$budgets = Budget::getOptions(array("USER_ID" => $user->getId(), "ACTIVE" => 1));
		$spent = array();
		
		foreach ($budgets as $key => $item) {
            $activities = Activity::getOptions(array("USER_ID" => $user->getId(), "CATEGORY_ID" => $item['category_id'], "TRANSACTION_DATE_START" => Date::firstOfMonth()));
            $value = 0;
            
            foreach ($activities as $activityKey => $activityItem) {
                $value += $activityItem['amount'];
            }
            
            $spent[$key] = $value;
		}
		
		$smarty->assign('spent', $spent);
		$smarty->assign('budgets', $budgets);
		
		if ($fullPage) {
            $userCategories = Category::getOptions(array("USER_ID" => $user->getId(), "ACTIVE" => 1));
            $allCategories = Category::getOptions(array("ACTIVE" => 1));
    		
    		$smarty->assign('allCategories', $allCategories);
    		$smarty->assign('userCategories', $userCategories);
    		$smarty->assign('user', $user);
    		$smarty->assign('left_menu', true);
    		$smarty->display('budget.tpl');
		} else {
            echo $smarty->fetch('budget_table.tpl');
		}
		
	} catch (AccessDeniedException $e) {
		trigger_error('Access Denied');
	} catch (Exception $e) {
		trigger_error('An error has occurred, please try again in a few minutes');
	}
	
?>