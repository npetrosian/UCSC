# -*- coding: utf-8 -*-
# this file is released under public domain and you can use without limitations

# -------------------------------------------------------------------------
# This is a sample controller
# - index is the default action of any application
# - user is required for authentication and authorization
# - download is for downloading files uploaded in the db (does streaming)
# -------------------------------------------------------------------------


def index():
    grid = SQLFORM.grid(db.product,
        create=True, editable=True, 
    )
    return dict(grid=grid)


def store():
    """Returns the store page, with the list of products to be bought"""

    # Initialize an empty array of links
    links = []

    # Let's add a button for Buy
    if(auth.user is not None):
        links.append(
            dict(header='',
            body = lambda row : 
            SPAN(A('Buy', 
                _href=URL('default', 'create_order', args=[row.id], user_signature=True),
                _class='btn')
                )
            )
        )

    grid = SQLFORM.grid(db.product,
        create=True, 
        editable=True, 
        links = links,
    )


    return dict(grid=grid)

@auth.requires_login()
def create_product():
    """More sophisticated way, in which we use web2py to come up with the form."""
    form = SQLFORM(db.product)
    # We can process the form.  This will check that the request is a POST,
    # and also perform validation, but in this case there is no validation.
    # THIS process() also inserts.
    if form.process().accepted:
        redirect(URL('default', 'store'))
    # We ask web2py to lay out the form for us.
    logger.info("My session is: %r" % session)
    return dict(form=form)

@auth.requires_login()
def create_profile():
    form = SQLFORM(db.profile)
    if form.process().accepted:
        redirect(URL('default', 'profile'))
    logger.info("My session is: %r" % session)
    return dict(form=form)

@auth.requires_login()
def create_order():
    """Page to create an order, accessed from the Buy button."""
    # product = db.product(request.args(0))
    # profile = db(db.profile.email == auth.user.email).select().first()
    # if profile is None:
    #     redirect(URL('default', 'profile',
    #                  vars=dict(next=URL('default', 'create_order', args=[product.id]),
    #                            edit='y')))
    # # Ok, here you know the profile exists.
    # # Sets the default for the order to be created. 
    # db.orders.product_id.default = product.id
    # db.orders.user.default = auth.user.email
    # db.orders.order_date.default = datetime.datetime.utcnow()
    # Complete.  You have to create a form for inserting an order, and process/return it.

    logger.info("First argument to create order: %r" % request.args[0])
    prec = db(db.product.id == request.args[0]).select().first()

    user_email = request.vars.email or auth.user.email
    logger.info("User email is: %r" % user_email)

    profile_record = db(db.profile.profile_email == user_email).select().first()

    product = db(db.product.id == request.args[0]).select().first()


    if profile_record is None:
        logger.info("The profile doesn't exist")
        redirect(URL('default', 'profile',
                      vars=dict(next=URL('default', 'create_order', args=[product.id]),
                                edit='y')))

    # logger.info("Profile email is: %r" % profile_record.profile_email)

    # record = db(db.profile.profile_email == user_email).select().first()

    product = db(db.product.id == request.args[0]).select().first()
    db.orders.orders_quantity.requires = IS_INT_IN_RANGE(1, product.product_quantity + 1)

    form = SQLFORM(db.orders) 

    if form.validate():
        logger.info("I just clicked on submit")
        logger.info("product.product_name = %r" % prec.product_name)
        logger.info("product.product_quantity = %r" % prec.product_quantity)
        logger.info("product.sales_price = %r" % prec.sales_price)
        logger.info("user_email = %r" % user_email)
        # total_paid = 999.99
        total_paid = prec.sales_price * int(request.vars.orders_quantity)
        db.orders.insert(
            orders_quantity = request.vars.orders_quantity,
            orders_product_id = prec.id,
            # product_name = product.product_name
            orders_amount_paid = total_paid,
            orders_email = profile_record.id

            )

        return redirect(URL('default', 'store'))

    else:
        return dict(title=prec.product_name, form=form)

@auth.requires_login()
def profile():
    """Page for creating/editing/viewing a profile. 
    It has two modes: edit/create, and view."""
    # This is the email of the user to which the form applies.
    user_email = request.vars.email or auth.user.email
    if request.vars.edit == 'y':
        # Mode for create/edit. 
        # You need to create a form to create (if there is no profile)
        # or edit (if there is a profile) the profile for the user.

        # This was form = None (a placeholder)
        # We need to complete it
        record = db(db.profile.profile_email == user_email).select().first()

        form = SQLFORM(db.profile, record) 
        if form.process().accepted:
            redirect(request.vars.next or URL('default', 'index'))

    else:
        # Mode for view.
        # You need to read the profile for the user, and return a view form for it, 
        # generated with SQLFORM(db.profile, profile, readonly=True). 
        # You do not need to process the form.

        # Get the pertinent record from the profile database which contains user_email
        record = db(db.profile.profile_email == user_email).select().first()
        form = SQLFORM(db.profile, record, readonly=True)   

    return dict(form=form)


@auth.requires_login()
def order_list():
    """Page to display the list of orders."""
    # Fixes visualization of email and product.  I hope this works, it should give you the idea at least.
    # db.orders.orders_email.represent = lambda v, r : A(v, _href=URL('default', 'profile', vars=dict(email=v)))
    db.orders.orders_email.represent = lambda v, r : A(get_profile_email(db.profile(v)), _href=URL('default', 'view_profile', args=[v]))

    db.orders.orders_product_id.represent = lambda v, r : A(get_product_name(db.product(v)), _href=URL('default', 'view_product', args=[v]))
    grid = SQLFORM.grid(db.orders,
        # Complete if needed.
    )
    return dict(grid=grid)

def view_profile():
    """Controller to view a product."""
    p = db.profile(request.args(0))
    if p is None:
        form = P('No such profile')
    else:
        form = SQLFORM(db.profile, p, readonly=True)
    return dict(form=form)


def view_product():
    """Controller to view a product."""
    p = db.product(request.args(0))
    if p is None:
        form = P('No such product')
    else:
        form = SQLFORM(db.product, p, readonly=True)
    return dict(form=form)


def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    http://..../[app]/default/user/bulk_register
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    also notice there is http://..../[app]/appadmin/manage/auth to allow administrator to manage users
    """
    return dict(form=auth())


@cache.action()
def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)


def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()


