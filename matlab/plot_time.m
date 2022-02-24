clear all
close all
clc

load('optimizer_stats_good.mat')

%% plot opt time
figure(1)
hold on 

% cut vertices
opt_time = opt_time(find(time > 72));
time = time(find(time > 72));

time = time - ones(1,length(time))*time(1);
opt_time = opt_time(find(time < 100));
time = time(find(time < 100));

% filter
d1 = designfilt('lowpassiir','FilterOrder',12, ...
    'HalfPowerFrequency',0.15,'DesignMethod','butter');
opt_time_filt = filtfilt(d1, opt_time);

% plot
plot(time, opt_time, 'LineWidth', 1, 'Color', '#9FBBD6')
plot(time, opt_time_filt, 'LineWidth',5)
set(gca, 'LineWidth', 3)
% set(gca, 'TickLabelInterpreter', 'latex')
set(gca, 'FontSize', 30)
set(gcf, 'Color', 'white')
ylim([0.0, 0.1])
xlabel('Time [s]')
ylabel('Planning Time [s]')

xline(17, 'k--', 'LineWidth', 2)
xline(53, 'k--', 'LineWidth', 2)
text(1, 0.09, {'Adding', 'obstacle 1'}, 'FontSize', 30)
text(23, 0.09, "Adding obstacle 2", 'FontSize', 30)
text(66, 0.09, "Replay trajectory", 'FontSize', 30)

%% plot kin_error
load('optimizer_stats_good.mat', 'time')
kin_err_wheel_1_z_end = kin_err_wheel_1_z_end(find(time > 125 & time < 172));
kin_err_wheel_2_z_end = kin_err_wheel_2_z_end(find(time > 125 & time < 172));
kin_err_wheel_3_z_end = kin_err_wheel_3_z_end(find(time > 125 & time < 172));
kin_err_wheel_4_z_end = kin_err_wheel_4_z_end(find(time > 125 & time < 172));
kin_err_wheel_1_z_init = kin_err_wheel_1_z_init(find(time > 125 & time < 172));
kin_err_wheel_2_z_init = kin_err_wheel_2_z_init(find(time > 125 & time < 172));
kin_err_wheel_3_z_init = kin_err_wheel_3_z_init(find(time > 125 & time < 172));
kin_err_wheel_4_z_init = kin_err_wheel_4_z_init(find(time > 125 & time < 172));

kin_err_wheel_1_z_init = kin_err_wheel_1_z_init ./ (ones(1, length(kin_err_wheel_1_z_init))*2);
%kin_err_wheel_2_z_init = kin_err_wheel_2_z_init ./ (ones(1, length(kin_err_wheel_2_z_init))*2);
%kin_err_wheel_3_z_init = kin_err_wheel_3_z_init ./ (ones(1, length(kin_err_wheel_3_z_init))*2);
%kin_err_wheel_4_z_init = kin_err_wheel_4_z_init ./ (ones(1, length(kin_err_wheel_4_z_init))*2);

time = time(find(time > 125 & time < 172));
time = time - ones(1,length(time))*72;

% kin_err_wheel_1_z_end = kin_err_wheel_1_z_end(find(time < 100));
% kin_err_wheel_2_z_end = kin_err_wheel_2_z_end(find(time < 100));
% kin_err_wheel_3_z_end = kin_err_wheel_3_z_end(find(time < 100));
% kin_err_wheel_4_z_end = kin_err_wheel_4_z_end(find(time < 100));
% time = time(find(time < 100));

fig = figure(2)

subplot(4,1,1)
hold on
grid on
plot(time, kin_err_wheel_1_z_init, 'LineWidth', 5)
plot(time, kin_err_wheel_1_z_end, 'LineWidth', 5)
set(gca, 'LineWidth', 2)
% set(gca, 'TickLabelInterpreter', 'latex')
set(gca, 'FontSize', 30)
set(gcf, 'Color', 'white')
legend('first','last')
ylim([-0.15, 0.15])
% title('Wheel FL')
subplot(4,1,2)
hold on
grid on
plot(time, kin_err_wheel_2_z_init, 'LineWidth', 5)
plot(time, kin_err_wheel_2_z_end, 'LineWidth', 5)
set(gca, 'LineWidth', 2)
% set(gca, 'TickLabelInterpreter', 'latex')
set(gca, 'FontSize', 30)
set(gcf, 'Color', 'white')
ylim([-0.15, 0.15])
% title('Wheel FR')
subplot(4,1,3)
hold on
grid on
plot(time, kin_err_wheel_3_z_init, 'LineWidth', 5)
plot(time, kin_err_wheel_3_z_end, 'LineWidth', 5)
set(gca, 'LineWidth', 2)
% set(gca, 'TickLabelInterpreter', 'latex')
set(gca, 'FontSize', 30)
set(gcf, 'Color', 'white')
ylim([-0.15, 0.15])
% title('Wheel RL')
subplot(4,1,4)
hold on
grid on
plot(time, kin_err_wheel_4_z_init, 'LineWidth', 5)
plot(time, kin_err_wheel_4_z_end, 'LineWidth', 5)
set(gca, 'LineWidth', 2)
% set(gca, 'TickLabelInterpreter', 'latex')
set(gca, 'FontSize', 30)
set(gcf, 'Color', 'white')
ylim([-0.15, 0.15])
% title('Wheel RR', 'FontSize', 20)

han=axes(fig,'visible','off'); 
han.XLabel.Visible='on';
han.YLabel.Visible='on';
xlabel(han, 'Time [s]', 'FontSize', 30);
label = ylabel(han, 'Error [m]', 'FontSize', 30);
label.Position(1) = -0.09;

%% collision error
load('optimizer_stats_good.mat')

coll_err_init = coll_err_init(find(time > 125 & time < 172));
coll_err_end = coll_err_end(find(time > 125 & time < 172));
time = time(find(time > 125 & time < 172));
time = time - ones(1, length(time)) * 72;

figure(3)
hold on
grid on
set(gca, 'LineWidth', 2)
% set(gca, 'TickLabelInterpreter', 'latex')
set(gca, 'FontSize', 30)
set(gcf, 'Color', 'white')
plot(time, coll_err_init, 'LineWidth', 5)
plot(time, coll_err_end, 'LineWidth', 5)
xlabel('Time [s]')
ylabel('Error')
legend('first', 'last')
