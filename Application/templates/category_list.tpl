<table>
    <thead>
    	<tr>
    		<td colspan="2"><div id="status" style="height:2em;"></div></td>
    	</tr>
        <tr>
            <th style="font-size: large; font-weight: bold">Category</th>
            <th>&nbsp;</th>
        </tr>
    </thead>
    <tbody id="categoryRows">
        {foreach from=$allCategories key=k item=v}
            <tr>
                <td>{$v}</td>
                <td>&nbsp;</td>
            </tr>
        {/foreach}   
        {foreach from=$userCategories key=k item=v}
            <tr>
                <td>{$v}</td>
                <td><input type="button" value="Remove" onclick="removeCategory(this, {$k})" /></td>
            </tr>
        {/foreach}                  
    </tbody>
</table>
