[% IF whole.error %]
[% IF whole.status == 'missing_identifier' %]
<p><em>Please Note:</em> Mandatory field Identifier is missing.</p>
[% ELSIF whole.status == 'missing_branch' %]
<p><em>Please Note:</em> Branch is a mandatory field.</p>
[% ELSIF whole.status == 'invalid_borrower' %]
<p><em>Please Note:</em> The borrower details you entered are invalid.</p>
[% ELSIF whole.status == 'invalid_branch' %]
<p><em>Please Note:</em> The branch you chose is invalid.</p>
[% ELSE %]
<p>Unhandled error</p>
[% END %]
[% END %]

[% IF whole.stage == "form" %]
<h2>Create a manual ILL request</h2>
<form id="mcpl_create_form" method="POST" action=[% here %]>
  [% INCLUDE 'csrf-token.inc' %]
  <fieldset class="rows">
    <legend>General details</legend>
    <ol id="general-mcpl-fields">
      <li>
        <label class="required" for="type">Type:</label>
        <select name="type" id="type">
          <option value=""/>
          [% IF whole.value.other.type.lower == "book" %]
          <option value="book" selected="selected">Book</option>
          [% ELSE %]
          <option value="book">Book</option>
          [% END %]
          [% IF whole.value.other.type.lower == "lpbook" %]
          <option value="lpbook" selected="selected">Large Print Book</option>
          [% ELSE %]
          <option value="lpbook">Large Print Book</option>
          [% END %]
          [% IF whole.value.other.type.lower == "journal" %]
          <option value="journal" selected="selected">Journal</option>
          [% ELSE %]
          <option value="journal">Journal</option>
          [% END %]
          [% IF whole.value.other.type.lower == "dvd" %]
          <option value="dvd" selected="selected">DVD</option>
          [% ELSE %]
          <option value="dvd">DVD</option>
          [% END %]
          [% IF whole.value.other.type.lower == "vgame" %]
          <option value="vgame" selected="selected">Video Game</option>
          [% ELSE %]
          <option value="vgame">Video Game</option>
          [% END %]
          [% IF whole.value.other.type.lower == "abook" %]
          <option value="abook" selected="selected">Audiobook</option>
          [% ELSE %]
          <option value="abook">Audiobook</option>
          [% END %]
          [% IF whole.value.other.type.lower == "cd" %]
          <option value="cd" selected="selected">Music CD</option>
          [% ELSE %]
          <option value="cd">Music CD</option>
          [% END %]
        </select>
      </li>
    </ol>
  </fieldset>
  [% cwd = whole.cwd %]
  [% type = whole.value.other.type %]
  [% IF type %]
      [% INCLUDE "${cwd}/shared-includes/forms/${type}.inc" %]
  [% END %]
  [% INCLUDE "${cwd}/shared-includes/custom_fields.inc" %]
  <fieldset class="rows">
    <legend>Patron options</legend>
    <ol>
      <li>
        <label class="required" for="cardnumber">
          Card number, username or surname:
        </label>
        <input type="text" name="cardnumber" id="cardnumber" autocomplete="off"
               type="text" value="" />
      </li>
      <li>
        <label class="required" for="branchcode">Destination library:</label>
        <select id="branchcode" name="branchcode">
          <option value="" />
          [% FOREACH branch IN branches %]
            <option value="[% branch.branchcode %]">
              [% branch.branchname %]
            </option>
          [% END %]
        </select>
      </li>
    </ol>
  </fieldset>
  <fieldset class="action">
    <input id="ill-submit" type="submit" value="Create" disabled />
    <a class="cancel" href="/cgi-bin/koha/ill/ill-requests.pl">Cancel</a>
  </fieldset>
  <input type="hidden" name="method" value="create" />
  <input type="hidden" name="stage" value="form" />
  <input type="hidden" name="backend" value="Mcpl" />
</form>
[% BLOCK backend_jsinclude %]
<script type="text/javascript">
    // <![CDATA[]
    [% INCLUDE "${cwd}/shared-includes/shared.js" %]
    // Require a username and branch selection
    document.addEventListener('DOMContentLoaded', function(){
        $('#mcpl_create_form #cardnumber, #mcpl_create_form #branchcode').change(function() {
            var comp = ['#cardnumber','#branchcode'].filter(function(id) {
                return $(id).val().length > 0;
            });
            $('#ill-submit').attr('disabled', comp.length < 2);
        });
        
		// Added for Koha 22.11
		patron_autocomplete(
        $('#mcpl_create_form #cardnumber'),
        {
          'on-select-callback': function( event, ui ) {
		   $("#mcpl_create_form #cardnumber").val( ui.item.cardnumber );
            return false;
          }
        }
      );
    });
    // ]]>
</script>
[% END %]

[% ELSIF whole.stage == "borrowers" %]
<!-- We need to clarify the borrower that has been requested. -->
<h2>Borrower selection</h2>
<form method="POST" action=[% here %]>
  [% FOREACH prop IN whole.value.other.keys %]
    [% IF prop != 'custom_key' &&  prop != 'custom_value' && prop != 'cardnumber' %]
    <input type="hidden" name="[% prop %]" value="[% whole.value.other.$prop %]">
    [% END %]
  [% END %]
  [% keys = whole.value.other.custom_key.split('\0') %]
  [% values = whole.value.other.custom_value.split('\0') %]
  [% i = 0 %]
  [% FOREACH key IN keys %]
    <input type="hidden" name="custom_key" value="[% key %]">
    <input type="hidden" name="custom_value" value="[% values.$i %]">
  [% i = i + 1 %]
  [% END %]
  <fieldset class="rows">
    <legend>Available borrowers for surname [% surname %]</legend>
    [% FOREACH opt IN whole.value %]
    [% IF opt.key == "brw" %]
    <ol>
      <li>
        <label class="required" for="brw">Borrower</label>
        <select name="cardnumber" id="cardnumber">
          <option value=""></option>
          [% FOREACH brw IN opt.value %]
          <option value="[% brw.cardnumber %]">
            [% brw.firstname %] [% brw.surname %] ([% brw.cardnumber %])
          </option>
          [% END %]
        </select>
      </li>
    </ol>
    [% END %]
    [% END %]
  </fieldset>
  <fieldset class="action">
    <input type="submit" value="Select"/>
    <a class="cancel" href=[% parent %]>Cancel</a>
  </fieldset>
</form>

[% ELSE %]
<p>Unknown stage.  This should not have happened.

[% END %]
