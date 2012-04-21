<table>
    <thead>
        <tr>
            <th>Category</th>
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
