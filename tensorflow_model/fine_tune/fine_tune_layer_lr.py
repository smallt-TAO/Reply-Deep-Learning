# _*_ coding = utf-8 _*_

with tf.Graph().as_default():
    variables_to_restore = []
    variables_to_train = []

    for var in slim.get_model_variables():
        excluded = False

        for exclusion in fine_tune_layers:
            if var.op.name.startswith(exclusion)
                excluded = True
                variables_to_train.append(var)
                break;

        if not excluded:
            variables_to_restore.append(var)

    grads = opt.compute_gradients(total_loss, variables_to_train)
    apply_gradient_op = opt.apply_gradients(grads, global_step=global_step)

    # if you want to apply diff learning rate
    capped_grads_and_vars = []
    for grad in grads:
        for update_vars in update_gradient_var:
            if grad[1] == update_vars:
                capped_grads_and_vars.append(grad[0], grad[1])
            else:
                capped_grads_and_vars.append(0.002*grad[0], grad[1])
    apply_gradient_op = opt.apply_gradients(capped_grads_and_vars, global_step=global_step)

    # restore the pretrained model
    with sess.as_default():
        if pretrained_model:
            init_fn = slim.assign_from_checkpoint_fn(pretrained_model,
                                                    variables_to_restore)
        init_fn(sess)


        
