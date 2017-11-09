# _*_ coding = utf-8 _*_

#tensorflow 中从ckpt文件中恢复指定的层或将指定的层不进行恢复:  
#tensorflow 中不同的layer指定不同的学习率  
  
with tf.Graph().as_default():  
        #存放的是需要恢复的层参数  
        variables_to_restore = []  
        #存放的是需要训练的层参数名,这里是没恢复的需要进行重新训练,实际上恢复了的参数也可以训练  
        variables_to_train = []  
        for var in slim.get_model_variables():  
            excluded = False  
            for exclusion in fine_tune_layers:  
            #比如fine tune layer中包含logits,bottleneck  
                if var.op.name.startswith(exclusion):  
                    excluded = True  
                    break  
            if not excluded:  
                variables_to_restore.append(var)  
                #print('var to restore :',var)  
            else:  
                variables_to_train.append(var)  
                #print('var to train: ',var)  
  
  
        #这里省略掉一些步骤,进入训练步骤:  
        #将variables_to_train,需要训练的参数给optimizer 的compute_gradients函数  
        grads = opt.compute_gradients(total_loss, variables_to_train)  
        #这个函数将只计算variables_to_train中的梯度  
        #然后将梯度进行应用:  
        apply_gradient_op = opt.apply_gradients(grads, global_step=global_step)  
        #也可以直接调用opt.minimize(total_loss,variables_to_train)  
        #minimize只是将compute_gradients与apply_gradients封装成了一个函数,实际上还是调用的这两个函数  
        #如果在梯度里面不同的参数需要不同的学习率,那么可以:  
  
        capped_grads_and_vars = []#[(MyCapper(gv[0]), gv[1]) for gv in grads_and_vars]  
        #update_gradient_vars是需要更新的参数,使用的是全局学习率  
        #对于不是update_gradient_vars的参数,将其梯度更新乘以0.0001,使用基本上不动  
        for grad in grads:  
            for update_vars  in update_gradient_vars:  
                if grad[1]==update_vars:  
                    capped_grads_and_vars.append((grad[0],grad[1]))  
                else:  
                    capped_grads_and_vars.append((0.0001*grad[0],grad[1]))  
  
        apply_gradient_op = opt.apply_gradients(capped_grads_and_vars, global_step=global_step)  
  
        #在恢复模型时:  
  
        with sess.as_default():  
  
            if pretrained_model:  
                print('Restoring pretrained model: %s' % pretrained_model)  
                init_fn = slim.assign_from_checkpoint_fn(  
                pretrained_model,  
                variables_to_restore)  
                init_fn(sess)  
            #这样就将指定的层参数没有恢复  
